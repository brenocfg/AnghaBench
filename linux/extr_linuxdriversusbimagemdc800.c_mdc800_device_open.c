#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_6__ {scalar_t__ state; int open; int pic_len; int /*<<< orphan*/  io_lock; TYPE_1__* dev; TYPE_2__* irq_urb; scalar_t__ camera_request_ready; scalar_t__ camera_busy; scalar_t__ download_left; scalar_t__ pic_index; scalar_t__ out_ptr; scalar_t__ out_count; scalar_t__ in_count; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NOT_CONNECTED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_3__* mdc800 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdc800_device_open (struct inode* inode, struct file *file)
{
	int retval=0;
	int errn=0;

	mutex_lock(&mdc800->io_lock);
	
	if (mdc800->state == NOT_CONNECTED)
	{
		errn=-EBUSY;
		goto error_out;
	}
	if (mdc800->open)
	{
		errn=-EBUSY;
		goto error_out;
	}

	mdc800->in_count=0;
	mdc800->out_count=0;
	mdc800->out_ptr=0;
	mdc800->pic_index=0;
	mdc800->pic_len=-1;
	mdc800->download_left=0;

	mdc800->camera_busy=0;
	mdc800->camera_request_ready=0;

	retval=0;
	mdc800->irq_urb->dev = mdc800->dev;
	retval = usb_submit_urb (mdc800->irq_urb, GFP_KERNEL);
	if (retval) {
		dev_err(&mdc800->dev->dev,
			"request USB irq fails (submit_retval=%i).\n", retval);
		errn = -EIO;
		goto error_out;
	}

	mdc800->open=1;
	dev_dbg(&mdc800->dev->dev, "Mustek MDC800 device opened.\n");

error_out:
	mutex_unlock(&mdc800->io_lock);
	return errn;
}