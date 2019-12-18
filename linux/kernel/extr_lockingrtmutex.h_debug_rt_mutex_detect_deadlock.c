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
struct rt_mutex_waiter {int dummy; } ;
typedef  enum rtmutex_chainwalk { ____Placeholder_rtmutex_chainwalk } rtmutex_chainwalk ;

/* Variables and functions */
 int RT_MUTEX_FULL_CHAINWALK ; 

__attribute__((used)) static inline bool debug_rt_mutex_detect_deadlock(struct rt_mutex_waiter *w,
						  enum rtmutex_chainwalk walk)
{
	return walk == RT_MUTEX_FULL_CHAINWALK;
}