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
struct knav_acc_info {int /*<<< orphan*/  mem_size; } ;
struct knav_range_info {int flags; int num_queues; struct knav_acc_channel* acc; struct knav_device* kdev; struct knav_acc_info acc_info; } ;
struct knav_device {int /*<<< orphan*/  dev; } ;
struct knav_acc_channel {int /*<<< orphan*/ * list_cpu; int /*<<< orphan*/ * list_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int RANGE_MULTI_QUEUE ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct knav_acc_channel*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages_exact (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int knav_acc_free_range(struct knav_range_info *range)
{
	struct knav_device *kdev = range->kdev;
	struct knav_acc_channel *acc;
	struct knav_acc_info *info;
	int channel, channels;

	info = &range->acc_info;

	if (range->flags & RANGE_MULTI_QUEUE)
		channels = 1;
	else
		channels = range->num_queues;

	for (channel = 0; channel < channels; channel++) {
		acc = range->acc + channel;
		if (!acc->list_cpu[0])
			continue;
		dma_unmap_single(kdev->dev, acc->list_dma[0],
				 info->mem_size, DMA_BIDIRECTIONAL);
		free_pages_exact(acc->list_cpu[0], info->mem_size);
	}
	devm_kfree(range->kdev->dev, range->acc);
	return 0;
}