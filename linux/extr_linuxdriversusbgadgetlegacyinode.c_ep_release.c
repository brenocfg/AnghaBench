#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {struct ep_data* private_data; } ;
struct TYPE_4__ {scalar_t__ bDescriptorType; } ;
struct TYPE_3__ {scalar_t__ bDescriptorType; } ;
struct ep_data {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  ep; TYPE_2__ hs_desc; TYPE_1__ desc; } ;

/* Variables and functions */
 scalar_t__ STATE_EP_DISABLED ; 
 scalar_t__ STATE_EP_UNBOUND ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_ep (struct ep_data*) ; 
 int /*<<< orphan*/  usb_ep_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ep_release (struct inode *inode, struct file *fd)
{
	struct ep_data		*data = fd->private_data;
	int value;

	value = mutex_lock_interruptible(&data->lock);
	if (value < 0)
		return value;

	/* clean up if this can be reopened */
	if (data->state != STATE_EP_UNBOUND) {
		data->state = STATE_EP_DISABLED;
		data->desc.bDescriptorType = 0;
		data->hs_desc.bDescriptorType = 0;
		usb_ep_disable(data->ep);
	}
	mutex_unlock(&data->lock);
	put_ep (data);
	return 0;
}