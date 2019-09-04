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

__attribute__((used)) static inline struct python_obs_callback *python_obs_timer_cb(
		struct python_obs_timer *timer)
{
	return &((struct python_obs_callback *)timer)[-1];
}