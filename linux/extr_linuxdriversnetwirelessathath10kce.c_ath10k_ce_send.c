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
struct ath10k_ce_pipe {struct ath10k* ar; } ;
struct ath10k_ce {int /*<<< orphan*/  ce_lock; } ;
struct ath10k {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 int ath10k_ce_send_nolock (struct ath10k_ce_pipe*,void*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int ath10k_ce_send(struct ath10k_ce_pipe *ce_state,
		   void *per_transfer_context,
		   dma_addr_t buffer,
		   unsigned int nbytes,
		   unsigned int transfer_id,
		   unsigned int flags)
{
	struct ath10k *ar = ce_state->ar;
	struct ath10k_ce *ce = ath10k_ce_priv(ar);
	int ret;

	spin_lock_bh(&ce->ce_lock);
	ret = ath10k_ce_send_nolock(ce_state, per_transfer_context,
				    buffer, nbytes, transfer_id, flags);
	spin_unlock_bh(&ce->ce_lock);

	return ret;
}