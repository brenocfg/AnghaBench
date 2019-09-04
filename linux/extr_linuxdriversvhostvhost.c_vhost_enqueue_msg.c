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
struct vhost_msg_node {int /*<<< orphan*/  node; } ;
struct vhost_dev {int /*<<< orphan*/  wait; int /*<<< orphan*/  iotlb_lock; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_poll (int /*<<< orphan*/ *,int) ; 

void vhost_enqueue_msg(struct vhost_dev *dev, struct list_head *head,
		       struct vhost_msg_node *node)
{
	spin_lock(&dev->iotlb_lock);
	list_add_tail(&node->node, head);
	spin_unlock(&dev->iotlb_lock);

	wake_up_interruptible_poll(&dev->wait, EPOLLIN | EPOLLRDNORM);
}