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
typedef  int u32 ;
struct timer_base {int dummy; } ;

/* Variables and functions */
 size_t BASE_DEF ; 
 size_t BASE_STD ; 
 int /*<<< orphan*/  CONFIG_NO_HZ_COMMON ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int TIMER_DEFERRABLE ; 
 struct timer_base* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * timer_bases ; 

__attribute__((used)) static inline struct timer_base *get_timer_this_cpu_base(u32 tflags)
{
	struct timer_base *base = this_cpu_ptr(&timer_bases[BASE_STD]);

	/*
	 * If the timer is deferrable and NO_HZ_COMMON is set then we need
	 * to use the deferrable base.
	 */
	if (IS_ENABLED(CONFIG_NO_HZ_COMMON) && (tflags & TIMER_DEFERRABLE))
		base = this_cpu_ptr(&timer_bases[BASE_DEF]);
	return base;
}