#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mg_connection {TYPE_1__* listener; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {scalar_t__ user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
#define  MG_EV_CLOSE 129 
#define  MG_EV_HTTP_REQUEST 128 
 int /*<<< orphan*/  MG_F_SEND_AND_CLOSE ; 
 int /*<<< orphan*/  mg_printf (struct mg_connection*,char*) ; 

__attribute__((used)) static void handle_hello5(struct mg_connection *nc, int ev, void *ev_data) {
  (void) ev_data;
  switch (ev) {
    case MG_EV_HTTP_REQUEST:
      mg_printf(nc, "HTTP/1.0 200 OK\r\n\r\n[I am Hello again]");
      nc->flags |= MG_F_SEND_AND_CLOSE;
      break;
    case MG_EV_CLOSE:
      DBG(("%p == hello5 close", nc));
      (*(int *) nc->listener->user_data) += 1000;
      break;
  }
}