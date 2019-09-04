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
struct visor_device {int timer_active; int /*<<< orphan*/  device; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dev_stop_periodic_work(struct visor_device *dev)
{
	if (!dev->timer_active)
		return;

	del_timer_sync(&dev->timer);
	dev->timer_active = false;
	put_device(&dev->device);
}