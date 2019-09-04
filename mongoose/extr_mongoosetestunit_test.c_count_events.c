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
struct simple_data {int /*<<< orphan*/  fail; int /*<<< orphan*/  num_timer; int /*<<< orphan*/  num_close; int /*<<< orphan*/  num_send; int /*<<< orphan*/  num_recv; int /*<<< orphan*/  num_connect; int /*<<< orphan*/  num_accept; } ;

/* Variables and functions */
#define  MG_EV_ACCEPT 134 
#define  MG_EV_CLOSE 133 
#define  MG_EV_CONNECT 132 
#define  MG_EV_POLL 131 
#define  MG_EV_RECV 130 
#define  MG_EV_SEND 129 
#define  MG_EV_TIMER 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void count_events(struct simple_data *d, int ev) {
  switch (ev) {
    case MG_EV_POLL:
      break;
    case MG_EV_ACCEPT:
      d->num_accept++;
      break;
    case MG_EV_CONNECT:
      d->num_connect++;
      break;
    case MG_EV_RECV:
      d->num_recv++;
      break;
    case MG_EV_SEND:
      d->num_send++;
      break;
    case MG_EV_CLOSE:
      d->num_close++;
      break;
    case MG_EV_TIMER:
      d->num_timer++;
      break;
    default: {
      char msg[100];
      sprintf(msg, "(unexpected event: %d)", ev);
      strcat(d->fail, msg);
    }
  }
}