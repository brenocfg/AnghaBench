#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENODEV ; 
 int __rb4xx_cpld_change_cfg (TYPE_1__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* rb4xx_cpld ; 

int rb4xx_cpld_change_cfg(unsigned mask, unsigned value)
{
	int ret;

	if (rb4xx_cpld == NULL)
		return -ENODEV;

	mutex_lock(&rb4xx_cpld->lock);
	ret = __rb4xx_cpld_change_cfg(rb4xx_cpld, mask, value);
	mutex_unlock(&rb4xx_cpld->lock);

	return ret;
}