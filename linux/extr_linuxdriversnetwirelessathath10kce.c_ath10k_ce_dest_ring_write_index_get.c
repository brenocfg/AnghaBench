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
typedef  scalar_t__ u32 ;
struct ath10k {TYPE_1__* hw_ce_regs; } ;
struct TYPE_2__ {scalar_t__ dst_wr_index_addr; } ;

/* Variables and functions */
 scalar_t__ ath10k_ce_read32 (struct ath10k*,scalar_t__) ; 

__attribute__((used)) static inline u32 ath10k_ce_dest_ring_write_index_get(struct ath10k *ar,
						      u32 ce_ctrl_addr)
{
	return ath10k_ce_read32(ar, ce_ctrl_addr +
				ar->hw_ce_regs->dst_wr_index_addr);
}