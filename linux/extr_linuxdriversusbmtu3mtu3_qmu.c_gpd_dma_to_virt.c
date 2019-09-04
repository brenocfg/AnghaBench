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
typedef  scalar_t__ u32 ;
struct qmu_gpd {int dummy; } ;
struct mtu3_gpd_ring {int dma; struct qmu_gpd* start; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 scalar_t__ MAX_GPD_NUM ; 

__attribute__((used)) static struct qmu_gpd *gpd_dma_to_virt(struct mtu3_gpd_ring *ring,
		dma_addr_t dma_addr)
{
	dma_addr_t dma_base = ring->dma;
	struct qmu_gpd *gpd_head = ring->start;
	u32 offset = (dma_addr - dma_base) / sizeof(*gpd_head);

	if (offset >= MAX_GPD_NUM)
		return NULL;

	return gpd_head + offset;
}