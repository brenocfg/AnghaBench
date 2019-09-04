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
struct virtproc_info {TYPE_2__* vdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  release; struct device* parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct rpmsg_device {scalar_t__ src; int announce; TYPE_3__ dev; TYPE_1__ id; int /*<<< orphan*/ * ops; int /*<<< orphan*/  dst; } ;
struct virtio_rpmsg_channel {struct rpmsg_device rpdev; struct virtproc_info* vrp; } ;
struct rpmsg_channel_info {scalar_t__ src; int /*<<< orphan*/  name; int /*<<< orphan*/  dst; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ RPMSG_ADDR_ANY ; 
 int /*<<< orphan*/  RPMSG_NAME_SIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct virtio_rpmsg_channel* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct device* rpmsg_find_device (struct device*,struct rpmsg_channel_info*) ; 
 int rpmsg_register_device (struct rpmsg_device*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_rpmsg_ops ; 
 int /*<<< orphan*/  virtio_rpmsg_release_device ; 

__attribute__((used)) static struct rpmsg_device *rpmsg_create_channel(struct virtproc_info *vrp,
						 struct rpmsg_channel_info *chinfo)
{
	struct virtio_rpmsg_channel *vch;
	struct rpmsg_device *rpdev;
	struct device *tmp, *dev = &vrp->vdev->dev;
	int ret;

	/* make sure a similar channel doesn't already exist */
	tmp = rpmsg_find_device(dev, chinfo);
	if (tmp) {
		/* decrement the matched device's refcount back */
		put_device(tmp);
		dev_err(dev, "channel %s:%x:%x already exist\n",
				chinfo->name, chinfo->src, chinfo->dst);
		return NULL;
	}

	vch = kzalloc(sizeof(*vch), GFP_KERNEL);
	if (!vch)
		return NULL;

	/* Link the channel to our vrp */
	vch->vrp = vrp;

	/* Assign public information to the rpmsg_device */
	rpdev = &vch->rpdev;
	rpdev->src = chinfo->src;
	rpdev->dst = chinfo->dst;
	rpdev->ops = &virtio_rpmsg_ops;

	/*
	 * rpmsg server channels has predefined local address (for now),
	 * and their existence needs to be announced remotely
	 */
	rpdev->announce = rpdev->src != RPMSG_ADDR_ANY;

	strncpy(rpdev->id.name, chinfo->name, RPMSG_NAME_SIZE);

	rpdev->dev.parent = &vrp->vdev->dev;
	rpdev->dev.release = virtio_rpmsg_release_device;
	ret = rpmsg_register_device(rpdev);
	if (ret)
		return NULL;

	return rpdev;
}