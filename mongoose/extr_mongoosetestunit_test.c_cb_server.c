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
struct simple_data {struct simple_data* sclient_data; struct mg_connection* sclient_nc; } ;
struct mg_connection {int /*<<< orphan*/  handler; struct simple_data* user_data; } ;

/* Variables and functions */
 int MG_EV_ACCEPT ; 
 int /*<<< orphan*/  cb_sclient ; 
 int /*<<< orphan*/  count_events (struct simple_data*,int) ; 

__attribute__((used)) static void cb_server(struct mg_connection *nc, int ev, void *ev_data) {
  struct simple_data *d = (struct simple_data *) nc->user_data;
  (void) ev_data;
  if (ev == MG_EV_ACCEPT) {
    d->sclient_nc = nc;
    nc->user_data = d = d->sclient_data;
    nc->handler = cb_sclient;
  }
  count_events(d, ev);
}