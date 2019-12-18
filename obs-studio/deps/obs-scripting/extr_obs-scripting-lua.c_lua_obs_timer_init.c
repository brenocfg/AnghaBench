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
 struct lua_obs_timer* first_timer ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_mutex ; 

__attribute__((used)) static inline void lua_obs_timer_init(struct lua_obs_timer *timer)
{
	pthread_mutex_lock(&timer_mutex);

	struct lua_obs_timer *next = first_timer;
	timer->next = next;
	timer->p_prev_next = &first_timer;
	if (next)
		next->p_prev_next = &timer->next;
	first_timer = timer;

	pthread_mutex_unlock(&timer_mutex);
}