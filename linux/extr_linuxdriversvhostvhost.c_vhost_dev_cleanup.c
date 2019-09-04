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
struct vhost_dev {int nvqs; int /*<<< orphan*/ * mm; int /*<<< orphan*/ * worker; int /*<<< orphan*/  work_list; int /*<<< orphan*/  wait; int /*<<< orphan*/ * iotlb; int /*<<< orphan*/ * umem; int /*<<< orphan*/ * log_ctx; TYPE_1__** vqs; } ;
struct TYPE_2__ {int /*<<< orphan*/ * call_ctx; scalar_t__ kick; int /*<<< orphan*/ * error_ctx; } ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  eventfd_ctx_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fput (scalar_t__) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_clear_msg (struct vhost_dev*) ; 
 int /*<<< orphan*/  vhost_dev_free_iovecs (struct vhost_dev*) ; 
 int /*<<< orphan*/  vhost_umem_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_vq_reset (struct vhost_dev*,TYPE_1__*) ; 
 int /*<<< orphan*/  wake_up_interruptible_poll (int /*<<< orphan*/ *,int) ; 

void vhost_dev_cleanup(struct vhost_dev *dev)
{
	int i;

	for (i = 0; i < dev->nvqs; ++i) {
		if (dev->vqs[i]->error_ctx)
			eventfd_ctx_put(dev->vqs[i]->error_ctx);
		if (dev->vqs[i]->kick)
			fput(dev->vqs[i]->kick);
		if (dev->vqs[i]->call_ctx)
			eventfd_ctx_put(dev->vqs[i]->call_ctx);
		vhost_vq_reset(dev, dev->vqs[i]);
	}
	vhost_dev_free_iovecs(dev);
	if (dev->log_ctx)
		eventfd_ctx_put(dev->log_ctx);
	dev->log_ctx = NULL;
	/* No one will access memory at this point */
	vhost_umem_clean(dev->umem);
	dev->umem = NULL;
	vhost_umem_clean(dev->iotlb);
	dev->iotlb = NULL;
	vhost_clear_msg(dev);
	wake_up_interruptible_poll(&dev->wait, EPOLLIN | EPOLLRDNORM);
	WARN_ON(!llist_empty(&dev->work_list));
	if (dev->worker) {
		kthread_stop(dev->worker);
		dev->worker = NULL;
	}
	if (dev->mm)
		mmput(dev->mm);
	dev->mm = NULL;
}