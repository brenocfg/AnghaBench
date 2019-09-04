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
struct subchannel {int /*<<< orphan*/  reg_mutex; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void css_sch_device_unregister(struct subchannel *sch)
{
	mutex_lock(&sch->reg_mutex);
	if (device_is_registered(&sch->dev))
		device_unregister(&sch->dev);
	mutex_unlock(&sch->reg_mutex);
}