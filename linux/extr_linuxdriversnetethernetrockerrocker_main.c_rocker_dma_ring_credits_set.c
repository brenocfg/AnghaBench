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
struct rocker_dma_ring_info {int /*<<< orphan*/  type; } ;
struct rocker {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DESC_CREDITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rocker_write32 (struct rocker const*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rocker_dma_ring_credits_set(const struct rocker *rocker,
					const struct rocker_dma_ring_info *info,
					u32 credits)
{
	if (credits)
		rocker_write32(rocker, DMA_DESC_CREDITS(info->type), credits);
}