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
#define  MG_EV_CONNECT 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void cb5(struct mg_connection *nc, int ev, void *ev_data) {
  switch (ev) {
    case MG_EV_CONNECT:
      sprintf((char *) nc->user_data, "%d", *(int *) ev_data);
      break;
    default:
      break;
  }
}