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
struct ath10k_ce_pipe {int dummy; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_ce_write32 (struct ath10k*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  shadow_sr_wr_ind_addr (struct ath10k*,struct ath10k_ce_pipe*) ; 

__attribute__((used)) static inline void
ath10k_ce_shadow_src_ring_write_index_set(struct ath10k *ar,
					  struct ath10k_ce_pipe *ce_state,
					  unsigned int value)
{
	ath10k_ce_write32(ar, shadow_sr_wr_ind_addr(ar, ce_state), value);
}