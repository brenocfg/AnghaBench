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
struct nvme_dev {int num_vecs; int /*<<< orphan*/  dev; } ;
struct blk_mq_tag_set {struct nvme_dev* driver_data; } ;

/* Variables and functions */
 int blk_mq_pci_map_queues (struct blk_mq_tag_set*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_pci_map_queues(struct blk_mq_tag_set *set)
{
	struct nvme_dev *dev = set->driver_data;

	return blk_mq_pci_map_queues(set, to_pci_dev(dev->dev),
			dev->num_vecs > 1 ? 1 /* admin queue */ : 0);
}