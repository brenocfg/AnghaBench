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
struct mg_mgr {int num_calls; int num_ifaces; TYPE_2__** ifaces; } ;
struct TYPE_4__ {TYPE_1__* vtable; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* poll ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

int mg_mgr_poll(struct mg_mgr *m, int timeout_ms) {
  int i, num_calls_before = m->num_calls;

  for (i = 0; i < m->num_ifaces; i++) {
    m->ifaces[i]->vtable->poll(m->ifaces[i], timeout_ms);
  }

  return (m->num_calls - num_calls_before);
}