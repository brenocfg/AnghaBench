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
struct sched_dl_entity {scalar_t__ dl_overrun; scalar_t__ dl_non_contending; scalar_t__ dl_yielded; scalar_t__ dl_throttled; scalar_t__ dl_density; scalar_t__ dl_bw; scalar_t__ flags; scalar_t__ dl_period; scalar_t__ dl_deadline; scalar_t__ dl_runtime; } ;
struct task_struct {struct sched_dl_entity dl; } ;

/* Variables and functions */

void __dl_clear_params(struct task_struct *p)
{
	struct sched_dl_entity *dl_se = &p->dl;

	dl_se->dl_runtime		= 0;
	dl_se->dl_deadline		= 0;
	dl_se->dl_period		= 0;
	dl_se->flags			= 0;
	dl_se->dl_bw			= 0;
	dl_se->dl_density		= 0;

	dl_se->dl_throttled		= 0;
	dl_se->dl_yielded		= 0;
	dl_se->dl_non_contending	= 0;
	dl_se->dl_overrun		= 0;
}