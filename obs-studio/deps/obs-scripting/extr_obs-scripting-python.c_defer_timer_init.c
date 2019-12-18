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
struct python_obs_timer {int dummy; } ;
struct python_obs_callback {int dummy; } ;

/* Variables and functions */
 struct python_obs_timer* python_obs_callback_extra_data (struct python_obs_callback*) ; 
 int /*<<< orphan*/  python_obs_timer_init (struct python_obs_timer*) ; 

__attribute__((used)) static void defer_timer_init(void *p_cb)
{
	struct python_obs_callback *cb = p_cb;
	struct python_obs_timer *timer = python_obs_callback_extra_data(cb);
	python_obs_timer_init(timer);
}