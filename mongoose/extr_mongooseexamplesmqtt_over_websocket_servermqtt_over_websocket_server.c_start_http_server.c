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
struct mg_mgr {int dummy; } ;
struct mg_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  http_handler ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void start_http_server(struct mg_mgr *mgr, const char *addr) {
  struct mg_connection *c;
  if ((c = mg_bind(mgr, addr, http_handler)) == NULL) {
    fprintf(stderr, "Cannot start HTTP server on port [%s]\n", addr);
    exit(EXIT_FAILURE);
  }
  mg_set_protocol_http_websocket(c);
  printf("HTTP server started on %s\n", addr);
}