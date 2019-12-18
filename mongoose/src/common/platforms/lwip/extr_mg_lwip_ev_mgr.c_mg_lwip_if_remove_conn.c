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
struct mg_ev_mgr_lwip_data {TYPE_2__* sig_queue; } ;
struct mg_connection {TYPE_1__* iface; } ;
struct TYPE_4__ {int /*<<< orphan*/  sig; struct mg_connection* nc; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int MG_SIG_QUEUE_LEN ; 
 int /*<<< orphan*/  MG_SIG_TOMBSTONE ; 

void mg_lwip_if_remove_conn(struct mg_connection *nc) {
  struct mg_ev_mgr_lwip_data *md =
      (struct mg_ev_mgr_lwip_data *) nc->iface->data;
  /* Walk the queue and null-out further signals for this conn. */
  for (int i = 0; i < MG_SIG_QUEUE_LEN; i++) {
    if (md->sig_queue[i].nc == nc) {
      md->sig_queue[i].sig = MG_SIG_TOMBSTONE;
    }
  }
}