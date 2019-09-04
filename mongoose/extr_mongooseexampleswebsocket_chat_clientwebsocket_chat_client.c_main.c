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
 int /*<<< orphan*/  ev_handler ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 struct mg_connection* mg_connect_ws (struct mg_mgr*,int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int) ; 
 int /*<<< orphan*/  s_done ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv) {
  struct mg_mgr mgr;
  struct mg_connection *nc;
  const char *chat_server_url = argc > 1 ? argv[1] : "ws://127.0.0.1:8000";

  mg_mgr_init(&mgr, NULL);

  nc = mg_connect_ws(&mgr, ev_handler, chat_server_url, "ws_chat", NULL);
  if (nc == NULL) {
    fprintf(stderr, "Invalid address\n");
    return 1;
  }

  while (!s_done) {
    mg_mgr_poll(&mgr, 100);
  }
  mg_mgr_free(&mgr);

  return 0;
}