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
 int /*<<< orphan*/  _IOLBF ; 
 int /*<<< orphan*/  ev_handler ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* s_http_port ; 
 TYPE_1__ s_http_server_opts ; 
 scalar_t__ s_signal_received ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_handler ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

int main(void) {
  struct mg_mgr mgr;
  struct mg_connection *nc;

  signal(SIGTERM, signal_handler);
  signal(SIGINT, signal_handler);
  setvbuf(stdout, NULL, _IOLBF, 0);
  setvbuf(stderr, NULL, _IOLBF, 0);

  mg_mgr_init(&mgr, NULL);

  nc = mg_bind(&mgr, s_http_port, ev_handler);
  mg_set_protocol_http_websocket(nc);
  s_http_server_opts.document_root = ".";  // Serve current directory
  s_http_server_opts.enable_directory_listing = "yes";

  printf("Started on port %s\n", s_http_port);
  while (s_signal_received == 0) {
    mg_mgr_poll(&mgr, 200);
  }
  mg_mgr_free(&mgr);

  return 0;
}