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
 struct mg_connection* mg_connect_http (struct mg_mgr*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ s_exit_flag ; 
 char* s_url ; 

int main(void) {
  struct mg_mgr mgr;
  struct mg_connection *nc;

  mg_mgr_init(&mgr, NULL);
  nc = mg_connect_http(&mgr, ev_handler, s_url, NULL, NULL);
  mg_set_protocol_http_websocket(nc);

  printf("Starting RESTful client against %s\n", s_url);
  while (s_exit_flag == 0) {
    mg_mgr_poll(&mgr, 1000);
  }
  mg_mgr_free(&mgr);

  return 0;
}