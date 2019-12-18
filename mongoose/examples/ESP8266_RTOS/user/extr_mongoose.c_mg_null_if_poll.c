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
typedef  int /*<<< orphan*/  time_t ;
struct mg_mgr {struct mg_connection* active_connections; } ;
struct mg_iface {struct mg_mgr* mgr; } ;
struct mg_connection {struct mg_connection* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  mg_if_poll (struct mg_connection*,double) ; 
 double mg_time () ; 

__attribute__((used)) static time_t mg_null_if_poll(struct mg_iface *iface, int timeout_ms) {
  struct mg_mgr *mgr = iface->mgr;
  struct mg_connection *nc, *tmp;
  double now = mg_time();
  /* We basically just run timers and poll. */
  for (nc = mgr->active_connections; nc != NULL; nc = tmp) {
    tmp = nc->next;
    mg_if_poll(nc, now);
  }
  (void) timeout_ms;
  return (time_t) now;
}