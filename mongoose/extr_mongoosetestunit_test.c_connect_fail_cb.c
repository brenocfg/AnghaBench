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
#define  MG_EV_CONNECT 128 

__attribute__((used)) static void connect_fail_cb(struct mg_connection *nc, int ev, void *p) {
  switch (ev) {
    case MG_EV_CONNECT:
      /* On connection success, set flag 1, else set 4 */
      *(int *) nc->user_data |= *(int *) p == 0 ? 1 : 4;
      break;
    case MG_EV_CLOSE:
      *(int *) nc->user_data |= 2;
      break;
  }
}