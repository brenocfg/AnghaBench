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
struct ath10k_ce_ring {unsigned int nentries_mask; unsigned int sw_index; unsigned int write_index; int /*<<< orphan*/ ** per_transfer_context; } ;
struct ath10k_ce_pipe {TYPE_1__* ops; struct ath10k* ar; struct ath10k_ce_ring* src_ring; } ;
struct ath10k_ce {int /*<<< orphan*/  ce_lock; } ;
struct ath10k {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* ce_extract_desc_data ) (struct ath10k*,struct ath10k_ce_ring*,unsigned int,int /*<<< orphan*/ *,unsigned int*,unsigned int*) ;} ;

/* Variables and functions */
 unsigned int CE_RING_IDX_INCR (unsigned int,unsigned int) ; 
 int EIO ; 
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ath10k*,struct ath10k_ce_ring*,unsigned int,int /*<<< orphan*/ *,unsigned int*,unsigned int*) ; 

int ath10k_ce_cancel_send_next(struct ath10k_ce_pipe *ce_state,
			       void **per_transfer_contextp,
			       dma_addr_t *bufferp,
			       unsigned int *nbytesp,
			       unsigned int *transfer_idp)
{
	struct ath10k_ce_ring *src_ring;
	unsigned int nentries_mask;
	unsigned int sw_index;
	unsigned int write_index;
	int ret;
	struct ath10k *ar;
	struct ath10k_ce *ce;

	src_ring = ce_state->src_ring;

	if (!src_ring)
		return -EIO;

	ar = ce_state->ar;
	ce = ath10k_ce_priv(ar);

	spin_lock_bh(&ce->ce_lock);

	nentries_mask = src_ring->nentries_mask;
	sw_index = src_ring->sw_index;
	write_index = src_ring->write_index;

	if (write_index != sw_index) {
		ce_state->ops->ce_extract_desc_data(ar, src_ring, sw_index,
						    bufferp, nbytesp,
						    transfer_idp);

		if (per_transfer_contextp)
			*per_transfer_contextp =
				src_ring->per_transfer_context[sw_index];

		/* sanity */
		src_ring->per_transfer_context[sw_index] = NULL;

		/* Update sw_index */
		sw_index = CE_RING_IDX_INCR(nentries_mask, sw_index);
		src_ring->sw_index = sw_index;
		ret = 0;
	} else {
		ret = -EIO;
	}

	spin_unlock_bh(&ce->ce_lock);

	return ret;
}