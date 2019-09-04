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
struct uio_listener {scalar_t__ event_count; struct uio_device* dev; } ;
struct uio_device {int /*<<< orphan*/  event; int /*<<< orphan*/  wait; int /*<<< orphan*/  info_lock; TYPE_1__* info; } ;
struct file {struct uio_listener* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EIO ; 
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t uio_poll(struct file *filep, poll_table *wait)
{
	struct uio_listener *listener = filep->private_data;
	struct uio_device *idev = listener->dev;
	__poll_t ret = 0;

	mutex_lock(&idev->info_lock);
	if (!idev->info || !idev->info->irq)
		ret = -EIO;
	mutex_unlock(&idev->info_lock);

	if (ret)
		return ret;

	poll_wait(filep, &idev->wait, wait);
	if (listener->event_count != atomic_read(&idev->event))
		return EPOLLIN | EPOLLRDNORM;
	return 0;
}