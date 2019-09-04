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
struct nvme_ns_head {int dummy; } ;
struct gendisk {struct nvme_ns_head* private_data; int /*<<< orphan*/ * fops; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct nvme_ns_head* head; } ;

/* Variables and functions */
 struct gendisk* dev_to_disk (struct device*) ; 
 int /*<<< orphan*/  nvme_fops ; 
 TYPE_1__* nvme_get_ns_from_dev (struct device*) ; 

__attribute__((used)) static inline struct nvme_ns_head *dev_to_ns_head(struct device *dev)
{
	struct gendisk *disk = dev_to_disk(dev);

	if (disk->fops == &nvme_fops)
		return nvme_get_ns_from_dev(dev)->head;
	else
		return disk->private_data;
}