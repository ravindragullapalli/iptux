//
// C++ Implementation: output
//
// Description:
//
//
// Author: Jally <jallyx@163.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "output.h"

#include <string>

#include "iptux/deplib.h"

using namespace std;

namespace iptux {

/**
 * 弹出消息提示.
 * @param parent parent window
 * @param format as in printf()
 * @param ...
 */
void pop_info(GtkWidget *parent, const gchar *format, ...) {
  GtkWidget *dialog;
  gchar *msg;
  va_list ap;

  va_start(ap, format);
  msg = g_strdup_vprintf(format, ap);
  va_end(ap);
  dialog = gtk_message_dialog_new(GTK_WINDOW(parent), GTK_DIALOG_MODAL,
                                  GTK_MESSAGE_INFO, GTK_BUTTONS_OK, NULL);
  gtk_message_dialog_set_markup(GTK_MESSAGE_DIALOG(dialog), msg);
  g_free(msg);
  gtk_window_set_title(GTK_WINDOW(dialog), _("Information"));
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

/**
 * 弹出警告信息.
 * @param parent parent window
 * @param format as in printf()
 * @param ...
 */
void pop_warning(GtkWidget *parent, const gchar *format, ...) {
  GtkWidget *dialog;
  gchar *msg;
  va_list ap;

  va_start(ap, format);
  msg = g_strdup_vprintf(format, ap);
  va_end(ap);
  dialog = gtk_message_dialog_new(GTK_WINDOW(parent), GTK_DIALOG_MODAL,
                                  GTK_MESSAGE_INFO, GTK_BUTTONS_OK, NULL);
  gtk_message_dialog_set_markup(GTK_MESSAGE_DIALOG(dialog), msg);
  g_free(msg);
  gtk_window_set_title(GTK_WINDOW(dialog), _("Warning"));
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

/**
 * 严重错误，程序将有可能自行强制退出.
 * @param format as in printf()
 * @param ...
 */
void pop_error(const gchar *format, ...) {
  GtkWidget *dialog;
  gchar *msg;
  va_list ap;

  va_start(ap, format);
  msg = g_strdup_vprintf(format, ap);
  va_end(ap);
  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_OK, NULL);
  gtk_message_dialog_set_markup(GTK_MESSAGE_DIALOG(dialog), msg);
  g_free(msg);
  gtk_window_set_title(GTK_WINDOW(dialog), _("Error"));
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

string pretty_fname(const string &fname) {
  size_t pos = fname.rfind("/src/");
  if (pos == string::npos) {
    return fname;
  } else {
    return fname.substr(pos + 5);
  }
}

void DoLog(const char *fname, int line, const char *func, GLogLevelFlags level,
           const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  gchar *msg = g_strdup_vprintf(format, ap);
  va_end(ap);
  g_log("iptux", level, "%s:%d:%s:%s", pretty_fname(fname).c_str(), line, func,
        msg);
  g_free(msg);
}

}  // namespace iptux
