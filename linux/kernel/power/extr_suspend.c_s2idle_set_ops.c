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
struct platform_s2idle_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_system_sleep () ; 
 struct platform_s2idle_ops const* s2idle_ops ; 
 int /*<<< orphan*/  unlock_system_sleep () ; 

void s2idle_set_ops(const struct platform_s2idle_ops *ops)
{
	lock_system_sleep();
	s2idle_ops = ops;
	unlock_system_sleep();
}