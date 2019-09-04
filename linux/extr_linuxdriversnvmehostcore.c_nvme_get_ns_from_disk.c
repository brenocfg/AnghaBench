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
struct gendisk {struct nvme_ns* private_data; } ;

/* Variables and functions */

__attribute__((used)) static struct nvme_ns *nvme_get_ns_from_disk(struct gendisk *disk,
		struct nvme_ns_head **head, int *srcu_idx)
{
#ifdef CONFIG_NVME_MULTIPATH
	if (disk->fops == &nvme_ns_head_ops) {
		*head = disk->private_data;
		*srcu_idx = srcu_read_lock(&(*head)->srcu);
		return nvme_find_path(*head);
	}
#endif
	*head = NULL;
	*srcu_idx = -1;
	return disk->private_data;
}