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
struct rocker_dma_ring_info {int size; int /*<<< orphan*/ * desc_info; scalar_t__ tail; scalar_t__ head; } ;
struct rocker {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  rocker_desc_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rocker_desc_head_set (struct rocker const*,struct rocker_dma_ring_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rocker_dma_ring_pass_to_producer(const struct rocker *rocker,
					     struct rocker_dma_ring_info *info)
{
	int i;

	BUG_ON(info->head || info->tail);

	/* When ring is consumer, we need to advance head for each desc.
	 * That tells hw that the desc is ready to be used by it.
	 */
	for (i = 0; i < info->size - 1; i++)
		rocker_desc_head_set(rocker, info, &info->desc_info[i]);
	rocker_desc_commit(&info->desc_info[i]);
}