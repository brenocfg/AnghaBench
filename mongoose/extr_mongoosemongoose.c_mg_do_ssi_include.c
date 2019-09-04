#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mg_serve_http_opts {char* document_root; char* ssi_pattern; } ;
struct mg_connection {int dummy; } ;
struct http_message {int dummy; } ;
typedef  int /*<<< orphan*/  sock_t ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DIRSEP ; 
 int MG_MAX_PATH ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mg_fopen (char*,char*) ; 
 int /*<<< orphan*/  mg_get_errno () ; 
 scalar_t__ mg_match_prefix (char*,int,char*) ; 
 int /*<<< orphan*/  mg_printf (struct mg_connection*,char*,char*,...) ; 
 int /*<<< orphan*/  mg_send_file_data (struct mg_connection*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_send_ssi_file (struct mg_connection*,struct http_message*,char*,int /*<<< orphan*/ *,int,struct mg_serve_http_opts const*) ; 
 int /*<<< orphan*/  mg_set_close_on_exec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 
 int sscanf (char*,char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* strrchr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mg_do_ssi_include(struct mg_connection *nc, struct http_message *hm,
                              const char *ssi, char *tag, int include_level,
                              const struct mg_serve_http_opts *opts) {
  char file_name[MG_MAX_PATH], path[MG_MAX_PATH], *p;
  FILE *fp;

  /*
   * sscanf() is safe here, since send_ssi_file() also uses buffer
   * of size MG_BUF_LEN to get the tag. So strlen(tag) is always < MG_BUF_LEN.
   */
  if (sscanf(tag, " virtual=\"%[^\"]\"", file_name) == 1) {
    /* File name is relative to the webserver root */
    snprintf(path, sizeof(path), "%s/%s", opts->document_root, file_name);
  } else if (sscanf(tag, " abspath=\"%[^\"]\"", file_name) == 1) {
    /*
     * File name is relative to the webserver working directory
     * or it is absolute system path
     */
    snprintf(path, sizeof(path), "%s", file_name);
  } else if (sscanf(tag, " file=\"%[^\"]\"", file_name) == 1 ||
             sscanf(tag, " \"%[^\"]\"", file_name) == 1) {
    /* File name is relative to the currect document */
    snprintf(path, sizeof(path), "%s", ssi);
    if ((p = strrchr(path, DIRSEP)) != NULL) {
      p[1] = '\0';
    }
    snprintf(path + strlen(path), sizeof(path) - strlen(path), "%s", file_name);
  } else {
    mg_printf(nc, "Bad SSI #include: [%s]", tag);
    return;
  }

  if ((fp = mg_fopen(path, "rb")) == NULL) {
    mg_printf(nc, "SSI include error: mg_fopen(%s): %s", path,
              strerror(mg_get_errno()));
  } else {
    mg_set_close_on_exec((sock_t) fileno(fp));
    if (mg_match_prefix(opts->ssi_pattern, strlen(opts->ssi_pattern), path) >
        0) {
      mg_send_ssi_file(nc, hm, path, fp, include_level + 1, opts);
    } else {
      mg_send_file_data(nc, fp);
    }
    fclose(fp);
  }
}