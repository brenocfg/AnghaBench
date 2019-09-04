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
struct lua_obs_timer {struct lua_obs_timer* next; struct lua_obs_timer** p_prev_next; } ;

/* Variables and functions */

__attribute__((used)) static inline void lua_obs_timer_remove(struct lua_obs_timer *timer)
{
	struct lua_obs_timer *next = timer->next;
	if (next) next->p_prev_next = timer->p_prev_next;
	*timer->p_prev_next = timer->next;
}