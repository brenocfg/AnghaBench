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
struct switch_dev {int /*<<< orphan*/  sw_mutex; int /*<<< orphan*/  dev_list; int /*<<< orphan*/  portbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swconfig_destroy_led_trigger (struct switch_dev*) ; 
 int /*<<< orphan*/  swconfig_lock () ; 
 int /*<<< orphan*/  swconfig_unlock () ; 

void
unregister_switch(struct switch_dev *dev)
{
	swconfig_destroy_led_trigger(dev);
	kfree(dev->portbuf);
	mutex_lock(&dev->sw_mutex);
	swconfig_lock();
	list_del(&dev->dev_list);
	swconfig_unlock();
	mutex_unlock(&dev->sw_mutex);
}