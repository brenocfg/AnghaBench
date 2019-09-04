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
struct rocker_dma_ring_info {int size; int /*<<< orphan*/  desc_info; int /*<<< orphan*/  mapaddr; int /*<<< orphan*/  desc; int /*<<< orphan*/  type; } ;
struct rocker_desc {int dummy; } ;
struct rocker {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DESC_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rocker_write64 (struct rocker const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rocker_dma_ring_destroy(const struct rocker *rocker,
				    const struct rocker_dma_ring_info *info)
{
	rocker_write64(rocker, DMA_DESC_ADDR(info->type), 0);

	pci_free_consistent(rocker->pdev,
			    info->size * sizeof(struct rocker_desc),
			    info->desc, info->mapaddr);
	kfree(info->desc_info);
}