#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mg_mgr {char* hexdump_file; } ;
struct mg_connection {int dummy; } ;
struct TYPE_4__ {char* document_root; } ;
struct TYPE_3__ {char* document_root; char* url_rewrites; } ;

/* Variables and functions */
 int /*<<< orphan*/  backend_handler ; 
 int /*<<< orphan*/  frontend_handler ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* s_backend_port ; 
 TYPE_2__ s_backend_server_opts ; 
 char* s_frontend_port ; 
 TYPE_1__ s_frontend_server_opts ; 
 scalar_t__ strcmp (char*,char*) ; 

int main(int argc, char *argv[]) {
  struct mg_mgr mgr;
  struct mg_connection *nc;
  int i;

  /* Open listening socket */
  mg_mgr_init(&mgr, NULL);

  /* configure frontend web server */
  nc = mg_bind(&mgr, s_frontend_port, frontend_handler);
  mg_set_protocol_http_websocket(nc);

  s_frontend_server_opts.document_root = "frontend";
  s_frontend_server_opts.url_rewrites =
      "/api=http://localhost:8001,/=frontend/hello.html";

  /* configure backend web server */
  nc = mg_bind(&mgr, s_backend_port, backend_handler);
  mg_set_protocol_http_websocket(nc);

  s_backend_server_opts.document_root = "backend";

  /* Parse command line arguments */
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-D") == 0) {
      mgr.hexdump_file = argv[++i];
    } else if (strcmp(argv[i], "-r") == 0) {
      s_frontend_server_opts.document_root = argv[++i];
    }
  }

  printf("Starting web server on port %s\n", s_frontend_port);
  for (;;) {
    mg_mgr_poll(&mgr, 1000);
  }
}