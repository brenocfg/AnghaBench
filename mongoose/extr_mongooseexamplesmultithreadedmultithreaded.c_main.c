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
struct mg_mgr {int dummy; } ;
struct mg_connection {int dummy; } ;
struct TYPE_2__ {char* document_root; char* enable_directory_listing; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_handler ; 
 int /*<<< orphan*/  exit (int) ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 
 scalar_t__ mg_socketpair (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_start_thread (int /*<<< orphan*/ ,struct mg_mgr*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* s_http_port ; 
 TYPE_1__ s_http_server_opts ; 
 int s_num_worker_threads ; 
 scalar_t__ s_received_signal ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_handler ; 
 int /*<<< orphan*/ * sock ; 
 int /*<<< orphan*/  worker_thread_proc ; 

int main(void) {
  struct mg_mgr mgr;
  struct mg_connection *nc;
  int i;

  if (mg_socketpair(sock, SOCK_STREAM) == 0) {
    perror("Opening socket pair");
    exit(1);
  }

  signal(SIGTERM, signal_handler);
  signal(SIGINT, signal_handler);

  mg_mgr_init(&mgr, NULL);

  nc = mg_bind(&mgr, s_http_port, ev_handler);
  if (nc == NULL) {
    printf("Failed to create listener\n");
    return 1;
  }

  mg_set_protocol_http_websocket(nc);
  s_http_server_opts.document_root = ".";  // Serve current directory
  s_http_server_opts.enable_directory_listing = "no";

  for (i = 0; i < s_num_worker_threads; i++) {
    mg_start_thread(worker_thread_proc, &mgr);
  }

  printf("Started on port %s\n", s_http_port);
  while (s_received_signal == 0) {
    mg_mgr_poll(&mgr, 200);
  }

  mg_mgr_free(&mgr);

  closesocket(sock[0]);
  closesocket(sock[1]);

  return 0;
}