#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mg_mgr {char* hexdump_file; } ;
struct mg_connection {int dummy; } ;
struct TYPE_2__ {char* document_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  db_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * db_open (char*) ; 
 int /*<<< orphan*/  ev_handler ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/ * s_db_handle ; 
 char* s_db_path ; 
 char* s_http_port ; 
 TYPE_1__ s_http_server_opts ; 
 scalar_t__ s_sig_num ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_handler ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 

int main(int argc, char *argv[]) {
  struct mg_mgr mgr;
  struct mg_connection *nc;
  int i;

  /* Open listening socket */
  mg_mgr_init(&mgr, NULL);
  nc = mg_bind(&mgr, s_http_port, ev_handler);
  mg_set_protocol_http_websocket(nc);
  s_http_server_opts.document_root = "web_root";

  /* Parse command line arguments */
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-D") == 0) {
      mgr.hexdump_file = argv[++i];
    } else if (strcmp(argv[i], "-f") == 0) {
      s_db_path = argv[++i];
    } else if (strcmp(argv[i], "-r") == 0) {
      s_http_server_opts.document_root = argv[++i];
    }
  }

  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);

  /* Open database */
  if ((s_db_handle = db_open(s_db_path)) == NULL) {
    fprintf(stderr, "Cannot open DB [%s]\n", s_db_path);
    exit(EXIT_FAILURE);
  }

  /* Run event loop until signal is received */
  printf("Starting RESTful server on port %s\n", s_http_port);
  while (s_sig_num == 0) {
    mg_mgr_poll(&mgr, 1000);
  }

  /* Cleanup */
  mg_mgr_free(&mgr);
  db_close(&s_db_handle);

  printf("Exiting on signal %d\n", s_sig_num);

  return 0;
}