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
struct virtproc_info {int /*<<< orphan*/  vdev; } ;
struct virtio_rpmsg_channel {struct virtproc_info* vrp; } ;
struct rpmsg_ns_msg {int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct rpmsg_device {TYPE_2__* ept; TYPE_1__ id; scalar_t__ announce; struct device dev; } ;
typedef  int /*<<< orphan*/  nsm ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPMSG_NAME_SIZE ; 
 int /*<<< orphan*/  RPMSG_NS_ADDR ; 
 int /*<<< orphan*/  RPMSG_NS_CREATE ; 
 int /*<<< orphan*/  VIRTIO_RPMSG_F_NS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int rpmsg_sendto (TYPE_2__*,struct rpmsg_ns_msg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct virtio_rpmsg_channel* to_virtio_rpmsg_channel (struct rpmsg_device*) ; 
 scalar_t__ virtio_has_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtio_rpmsg_announce_create(struct rpmsg_device *rpdev)
{
	struct virtio_rpmsg_channel *vch = to_virtio_rpmsg_channel(rpdev);
	struct virtproc_info *vrp = vch->vrp;
	struct device *dev = &rpdev->dev;
	int err = 0;

	/* need to tell remote processor's name service about this channel ? */
	if (rpdev->announce && rpdev->ept &&
	    virtio_has_feature(vrp->vdev, VIRTIO_RPMSG_F_NS)) {
		struct rpmsg_ns_msg nsm;

		strncpy(nsm.name, rpdev->id.name, RPMSG_NAME_SIZE);
		nsm.addr = rpdev->ept->addr;
		nsm.flags = RPMSG_NS_CREATE;

		err = rpmsg_sendto(rpdev->ept, &nsm, sizeof(nsm), RPMSG_NS_ADDR);
		if (err)
			dev_err(dev, "failed to announce service %d\n", err);
	}

	return err;
}