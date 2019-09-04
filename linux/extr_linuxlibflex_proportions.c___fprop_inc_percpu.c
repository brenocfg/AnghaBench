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
struct fprop_local_percpu {int /*<<< orphan*/  events; } ;
struct fprop_global {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROP_BATCH ; 
 int /*<<< orphan*/  fprop_reflect_period_percpu (struct fprop_global*,struct fprop_local_percpu*) ; 
 int /*<<< orphan*/  percpu_counter_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  percpu_counter_add_batch (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void __fprop_inc_percpu(struct fprop_global *p, struct fprop_local_percpu *pl)
{
	fprop_reflect_period_percpu(p, pl);
	percpu_counter_add_batch(&pl->events, 1, PROP_BATCH);
	percpu_counter_add(&p->events, 1);
}