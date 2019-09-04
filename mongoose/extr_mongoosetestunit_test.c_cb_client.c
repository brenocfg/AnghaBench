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
struct simple_data {int dummy; } ;
struct mg_connection {scalar_t__ user_data; } ;

/* Variables and functions */
#define  MG_EV_CONNECT 130 
#define  MG_EV_RECV 129 
#define  MG_EV_SEND 128 
 int /*<<< orphan*/  check_sent (struct simple_data*,struct mg_connection*,void*) ; 
 int /*<<< orphan*/  count_events (struct simple_data*,int) ; 
 int /*<<< orphan*/  do_recv (struct simple_data*,struct mg_connection*,void*) ; 
 int /*<<< orphan*/  do_send (struct simple_data*,struct mg_connection*) ; 

__attribute__((used)) static void cb_client(struct mg_connection *nc, int ev, void *ev_data) {
  struct simple_data *d = (struct simple_data *) nc->user_data;
  count_events(d, ev);
  switch (ev) {
    case MG_EV_CONNECT:
      do_send(d, nc);
      break;
    case MG_EV_SEND:
      check_sent(d, nc, ev_data);
      break;
    case MG_EV_RECV:
      do_recv(d, nc, ev_data);
      break;
  }
}