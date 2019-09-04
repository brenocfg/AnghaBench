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
struct TYPE_2__ {int /*<<< orphan*/ * paddrs_ring_32; } ;
struct ath10k_htt {TYPE_1__ rx_ring; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  __cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_htt_set_paddrs_ring_32(struct ath10k_htt *htt,
					  dma_addr_t paddr, int idx)
{
	htt->rx_ring.paddrs_ring_32[idx] = __cpu_to_le32(paddr);
}