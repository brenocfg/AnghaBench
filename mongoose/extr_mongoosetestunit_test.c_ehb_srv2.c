#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; } ;
struct mg_connection {TYPE_2__* mgr; TYPE_1__ recv_mbuf; } ;
struct TYPE_4__ {scalar_t__ user_data; } ;

/* Variables and functions */
 int MG_EV_CLOSE ; 

__attribute__((used)) static void ehb_srv2(struct mg_connection *c, int ev, void *p) {
  if (ev == MG_EV_CLOSE) {
    if (c->recv_mbuf.size == 1) (*(int *) c->mgr->user_data) = 1;
    (void) p;
  }
}