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
struct mg_connection {scalar_t__ user_data; } ;

/* Variables and functions */
#define  MG_EV_CLOSE 129 
#define  MG_EV_TIMER 128 

__attribute__((used)) static void ev_timer_handler(struct mg_connection *c, int ev, void *ev_data) {
  (void) ev_data;
  switch (ev) {
    case MG_EV_TIMER:
      (*(int *) c->user_data)++;
      break;
    case MG_EV_CLOSE:
      /* Make sure we're alive. Make the ASSERTs fail if we're here. */
      (*(int *) c->user_data) += 100;
      break;
  }
}