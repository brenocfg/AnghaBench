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
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int (* ce_rx_post_buf ) (struct ath10k_ce_pipe*,void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct ath10k_ce_pipe*,void*,int /*<<< orphan*/ ) ; 

int ath10k_ce_rx_post_buf(struct ath10k_ce_pipe *pipe, void *ctx,
			  dma_addr_t paddr)
{
	struct ath10k *ar = pipe->ar;
	struct ath10k_ce *ce = ath10k_ce_priv(ar);
	int ret;

	spin_lock_bh(&ce->ce_lock);
	ret = pipe->ops->ce_rx_post_buf(pipe, ctx, paddr);
	spin_unlock_bh(&ce->ce_lock);

	return ret;
}