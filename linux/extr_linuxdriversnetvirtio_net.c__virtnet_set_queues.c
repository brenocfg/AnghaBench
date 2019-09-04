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
typedef  int /*<<< orphan*/  u16 ;
struct virtnet_info {int /*<<< orphan*/  refill; int /*<<< orphan*/  curr_queue_pairs; TYPE_1__* ctrl; int /*<<< orphan*/  vdev; int /*<<< orphan*/  has_cvq; struct net_device* dev; } ;
struct scatterlist {int dummy; } ;
struct net_device {int flags; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  virtqueue_pairs; } ;
struct TYPE_3__ {TYPE_2__ mq; } ;

/* Variables and functions */
 int EINVAL ; 
 int IFF_UP ; 
 int /*<<< orphan*/  VIRTIO_NET_CTRL_MQ ; 
 int /*<<< orphan*/  VIRTIO_NET_CTRL_MQ_VQ_PAIRS_SET ; 
 int /*<<< orphan*/  VIRTIO_NET_F_MQ ; 
 int /*<<< orphan*/  cpu_to_virtio16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  virtio_has_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtnet_send_command (struct virtnet_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scatterlist*) ; 

__attribute__((used)) static int _virtnet_set_queues(struct virtnet_info *vi, u16 queue_pairs)
{
	struct scatterlist sg;
	struct net_device *dev = vi->dev;

	if (!vi->has_cvq || !virtio_has_feature(vi->vdev, VIRTIO_NET_F_MQ))
		return 0;

	vi->ctrl->mq.virtqueue_pairs = cpu_to_virtio16(vi->vdev, queue_pairs);
	sg_init_one(&sg, &vi->ctrl->mq, sizeof(vi->ctrl->mq));

	if (!virtnet_send_command(vi, VIRTIO_NET_CTRL_MQ,
				  VIRTIO_NET_CTRL_MQ_VQ_PAIRS_SET, &sg)) {
		dev_warn(&dev->dev, "Fail to set num of queue pairs to %d\n",
			 queue_pairs);
		return -EINVAL;
	} else {
		vi->curr_queue_pairs = queue_pairs;
		/* virtnet_open() will refill when device is going to up. */
		if (dev->flags & IFF_UP)
			schedule_delayed_work(&vi->refill, 0);
	}

	return 0;
}