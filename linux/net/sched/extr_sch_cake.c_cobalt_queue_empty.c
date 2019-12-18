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
struct cobalt_vars {scalar_t__ p_drop; int dropping; int /*<<< orphan*/  rec_inv_sqrt; int /*<<< orphan*/  drop_next; scalar_t__ count; int /*<<< orphan*/  blue_timer; } ;
struct cobalt_params {scalar_t__ target; scalar_t__ p_dec; int /*<<< orphan*/  interval; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  cobalt_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cobalt_invsqrt (struct cobalt_vars*) ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cobalt_queue_empty(struct cobalt_vars *vars,
			       struct cobalt_params *p,
			       ktime_t now)
{
	bool down = false;

	if (vars->p_drop &&
	    ktime_to_ns(ktime_sub(now, vars->blue_timer)) > p->target) {
		if (vars->p_drop < p->p_dec)
			vars->p_drop = 0;
		else
			vars->p_drop -= p->p_dec;
		vars->blue_timer = now;
		down = !vars->p_drop;
	}
	vars->dropping = false;

	if (vars->count && ktime_to_ns(ktime_sub(now, vars->drop_next)) >= 0) {
		vars->count--;
		cobalt_invsqrt(vars);
		vars->drop_next = cobalt_control(vars->drop_next,
						 p->interval,
						 vars->rec_inv_sqrt);
	}

	return down;
}