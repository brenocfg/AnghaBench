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
struct fprop_local_single {int /*<<< orphan*/  events; } ;
struct fprop_global {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprop_reflect_period_single (struct fprop_global*,struct fprop_local_single*) ; 
 int /*<<< orphan*/  percpu_counter_add (int /*<<< orphan*/ *,int) ; 

void __fprop_inc_single(struct fprop_global *p, struct fprop_local_single *pl)
{
	fprop_reflect_period_single(p, pl);
	pl->events++;
	percpu_counter_add(&p->events, 1);
}