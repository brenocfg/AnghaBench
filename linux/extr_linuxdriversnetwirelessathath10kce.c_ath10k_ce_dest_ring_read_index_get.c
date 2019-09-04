#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct ath10k_ce_pipe {int attr_flags; } ;
struct ath10k_ce {struct ath10k_ce_pipe* ce_states; } ;
struct TYPE_4__ {scalar_t__ rri_on_ddr; } ;
struct ath10k {TYPE_1__* hw_ce_regs; TYPE_2__ hw_params; } ;
struct TYPE_3__ {size_t current_drri_addr; } ;

/* Variables and functions */
 int CE_ATTR_DIS_INTR ; 
 size_t COPY_ENGINE_ID (size_t) ; 
 size_t ath10k_ce_dest_ring_read_index_from_ddr (struct ath10k*,size_t) ; 
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 size_t ath10k_ce_read32 (struct ath10k*,size_t) ; 

__attribute__((used)) static inline u32 ath10k_ce_dest_ring_read_index_get(struct ath10k *ar,
						     u32 ce_ctrl_addr)
{
	struct ath10k_ce *ce = ath10k_ce_priv(ar);
	u32 ce_id = COPY_ENGINE_ID(ce_ctrl_addr);
	struct ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	u32 index;

	if (ar->hw_params.rri_on_ddr &&
	    (ce_state->attr_flags & CE_ATTR_DIS_INTR))
		index = ath10k_ce_dest_ring_read_index_from_ddr(ar, ce_id);
	else
		index = ath10k_ce_read32(ar, ce_ctrl_addr +
					 ar->hw_ce_regs->current_drri_addr);

	return index;
}