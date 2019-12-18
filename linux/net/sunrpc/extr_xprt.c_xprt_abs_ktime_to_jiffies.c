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
typedef  int /*<<< orphan*/  s64 ;
typedef  scalar_t__ ktime_t ;

/* Variables and functions */
 unsigned long jiffies ; 
 scalar_t__ ktime_get () ; 
 int /*<<< orphan*/  ktime_to_ns (scalar_t__) ; 
 scalar_t__ likely (int) ; 
 unsigned long nsecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long xprt_abs_ktime_to_jiffies(ktime_t abstime)
{
	s64 delta = ktime_to_ns(ktime_get() - abstime);
	return likely(delta >= 0) ?
		jiffies - nsecs_to_jiffies(delta) :
		jiffies + nsecs_to_jiffies(-delta);
}