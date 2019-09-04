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
struct kiocb_priv {int dummy; } ;
struct kiocb {struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct file {int /*<<< orphan*/  f_flags; struct ep_data* private_data; } ;
struct ep_data {scalar_t__ state; int /*<<< orphan*/  lock; TYPE_1__* dev; int /*<<< orphan*/ * ep; int /*<<< orphan*/  name; int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EBADMSG ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIOCBQUEUED ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ STATE_EP_ENABLED ; 
 int /*<<< orphan*/  copy_from_iter_full (char*,size_t,struct iov_iter*) ; 
 int /*<<< orphan*/  ep_aio (struct kiocb*,struct kiocb_priv*,struct ep_data*,char*,size_t) ; 
 int /*<<< orphan*/  ep_config (struct ep_data*,char*,size_t) ; 
 int /*<<< orphan*/  ep_io (struct ep_data*,char*,size_t) ; 
 int /*<<< orphan*/  get_ready_ep (int /*<<< orphan*/ ,struct ep_data*,int) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 scalar_t__ is_sync_kiocb (struct kiocb*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 struct kiocb_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_endpoint_dir_in (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_endpoint_xfer_isoc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_ep_set_halt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
ep_write_iter(struct kiocb *iocb, struct iov_iter *from)
{
	struct file *file = iocb->ki_filp;
	struct ep_data *epdata = file->private_data;
	size_t len = iov_iter_count(from);
	bool configured;
	ssize_t value;
	char *buf;

	if ((value = get_ready_ep(file->f_flags, epdata, true)) < 0)
		return value;

	configured = epdata->state == STATE_EP_ENABLED;

	/* halt any endpoint by doing a "wrong direction" i/o call */
	if (configured && !usb_endpoint_dir_in(&epdata->desc)) {
		if (usb_endpoint_xfer_isoc(&epdata->desc) ||
		    !is_sync_kiocb(iocb)) {
			mutex_unlock(&epdata->lock);
			return -EINVAL;
		}
		DBG (epdata->dev, "%s halt\n", epdata->name);
		spin_lock_irq(&epdata->dev->lock);
		if (likely(epdata->ep != NULL))
			usb_ep_set_halt(epdata->ep);
		spin_unlock_irq(&epdata->dev->lock);
		mutex_unlock(&epdata->lock);
		return -EBADMSG;
	}

	buf = kmalloc(len, GFP_KERNEL);
	if (unlikely(!buf)) {
		mutex_unlock(&epdata->lock);
		return -ENOMEM;
	}

	if (unlikely(!copy_from_iter_full(buf, len, from))) {
		value = -EFAULT;
		goto out;
	}

	if (unlikely(!configured)) {
		value = ep_config(epdata, buf, len);
	} else if (is_sync_kiocb(iocb)) {
		value = ep_io(epdata, buf, len);
	} else {
		struct kiocb_priv *priv = kzalloc(sizeof *priv, GFP_KERNEL);
		value = -ENOMEM;
		if (priv) {
			value = ep_aio(iocb, priv, epdata, buf, len);
			if (value == -EIOCBQUEUED)
				buf = NULL;
		}
	}
out:
	kfree(buf);
	mutex_unlock(&epdata->lock);
	return value;
}