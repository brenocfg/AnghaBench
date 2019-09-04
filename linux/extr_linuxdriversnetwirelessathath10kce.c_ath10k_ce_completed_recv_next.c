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
struct ath10k_ce_pipe {TYPE_1__* ops; struct ath10k* ar; } ;
struct ath10k_ce {int /*<<< orphan*/  ce_lock; } ;
struct ath10k {int dummy; } ;
struct TYPE_2__ {int (* ce_completed_recv_next_nolock ) (struct ath10k_ce_pipe*,void**,unsigned int*) ;} ;

/* Variables and functions */
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct ath10k_ce_pipe*,void**,unsigned int*) ; 

int ath10k_ce_completed_recv_next(struct ath10k_ce_pipe *ce_state,
				  void **per_transfer_contextp,
				  unsigned int *nbytesp)
{
	struct ath10k *ar = ce_state->ar;
	struct ath10k_ce *ce = ath10k_ce_priv(ar);
	int ret;

	spin_lock_bh(&ce->ce_lock);
	ret = ce_state->ops->ce_completed_recv_next_nolock(ce_state,
						   per_transfer_contextp,
						   nbytesp);

	spin_unlock_bh(&ce->ce_lock);

	return ret;
}