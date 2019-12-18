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
struct hrtimer_cpu_base {int hres_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_HIGH_RES_TIMERS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __hrtimer_hres_active(struct hrtimer_cpu_base *cpu_base)
{
	return IS_ENABLED(CONFIG_HIGH_RES_TIMERS) ?
		cpu_base->hres_active : 0;
}