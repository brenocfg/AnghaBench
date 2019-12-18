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
struct work_result {unsigned long conn_id; int /*<<< orphan*/  sleep_time; } ;
struct mg_connection {int /*<<< orphan*/ * user_data; int /*<<< orphan*/  mgr; } ;

/* Variables and functions */
 struct mg_connection* mg_next (int /*<<< orphan*/ ,struct mg_connection*) ; 
 int /*<<< orphan*/  mg_printf (struct mg_connection*,char*,char*) ; 
 int /*<<< orphan*/  mg_send_head (struct mg_connection*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void on_work_complete(struct mg_connection *nc, int ev, void *ev_data) {
  (void) ev;
  char s[32];
  struct mg_connection *c;
  for (c = mg_next(nc->mgr, NULL); c != NULL; c = mg_next(nc->mgr, c)) {
    if (c->user_data != NULL) {
      struct work_result *res = (struct work_result *)ev_data;
      if ((unsigned long)c->user_data == res->conn_id) {
        sprintf(s, "conn_id:%lu sleep:%d", res->conn_id, res->sleep_time);
        mg_send_head(c, 200, strlen(s), "Content-Type: text/plain");
        mg_printf(c, "%s", s);
      }
    }
  }
}