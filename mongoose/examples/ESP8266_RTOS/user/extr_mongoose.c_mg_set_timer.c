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
struct mg_connection {double ev_timer_time; int flags; int /*<<< orphan*/ * priv_2; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int MG_F_RESOLVING ; 

double mg_set_timer(struct mg_connection *c, double timestamp) {
  double result = c->ev_timer_time;
  c->ev_timer_time = timestamp;
  /*
   * If this connection is resolving, it's not in the list of active
   * connections, so not processed yet. It has a DNS resolver connection
   * linked to it. Set up a timer for the DNS connection.
   */
  DBG(("%p %p %d -> %lu", c, c->priv_2, (c->flags & MG_F_RESOLVING ? 1 : 0),
       (unsigned long) timestamp));
  if ((c->flags & MG_F_RESOLVING) && c->priv_2 != NULL) {
    mg_set_timer((struct mg_connection *) c->priv_2, timestamp);
  }
  return result;
}