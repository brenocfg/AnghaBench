#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usbatm_data {int /*<<< orphan*/  thread_exited; int /*<<< orphan*/  serialize; int /*<<< orphan*/ * thread; int /*<<< orphan*/  usb_intf; TYPE_1__* driver; int /*<<< orphan*/  thread_started; } ;
struct TYPE_2__ {int (* heavy_init ) (struct usbatm_data*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  allow_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_and_exit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct usbatm_data*,int /*<<< orphan*/ ) ; 
 int usbatm_atm_init (struct usbatm_data*) ; 

__attribute__((used)) static int usbatm_do_heavy_init(void *arg)
{
	struct usbatm_data *instance = arg;
	int ret;

	allow_signal(SIGTERM);
	complete(&instance->thread_started);

	ret = instance->driver->heavy_init(instance, instance->usb_intf);

	if (!ret)
		ret = usbatm_atm_init(instance);

	mutex_lock(&instance->serialize);
	instance->thread = NULL;
	mutex_unlock(&instance->serialize);

	complete_and_exit(&instance->thread_exited, ret);
}