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
struct nvme_ns_head {int dummy; } ;
struct nvme_ns {int dummy; } ;
struct block_device {int /*<<< orphan*/  bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 struct nvme_ns* nvme_get_ns_from_disk (int /*<<< orphan*/ ,struct nvme_ns_head**,int*) ; 
 int nvme_ns_ioctl (struct nvme_ns*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  nvme_put_ns_from_disk (struct nvme_ns_head*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nvme_ioctl(struct block_device *bdev, fmode_t mode,
		unsigned int cmd, unsigned long arg)
{
	struct nvme_ns_head *head = NULL;
	struct nvme_ns *ns;
	int srcu_idx, ret;

	ns = nvme_get_ns_from_disk(bdev->bd_disk, &head, &srcu_idx);
	if (unlikely(!ns))
		ret = -EWOULDBLOCK;
	else
		ret = nvme_ns_ioctl(ns, cmd, arg);
	nvme_put_ns_from_disk(head, srcu_idx);
	return ret;
}