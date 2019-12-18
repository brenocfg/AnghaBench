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
struct cobalt_vars {int dropping; int count; void* drop_next; void* blue_timer; scalar_t__ p_drop; } ;
struct cobalt_params {scalar_t__ target; scalar_t__ p_inc; } ;
typedef  void* ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_sub (void*,void*) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cobalt_queue_full(struct cobalt_vars *vars,
			      struct cobalt_params *p,
			      ktime_t now)
{
	bool up = false;

	if (ktime_to_ns(ktime_sub(now, vars->blue_timer)) > p->target) {
		up = !vars->p_drop;
		vars->p_drop += p->p_inc;
		if (vars->p_drop < p->p_inc)
			vars->p_drop = ~0;
		vars->blue_timer = now;
	}
	vars->dropping = true;
	vars->drop_next = now;
	if (!vars->count)
		vars->count = 1;

	return up;
}