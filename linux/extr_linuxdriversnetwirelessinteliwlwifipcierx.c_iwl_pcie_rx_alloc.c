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
struct iwl_rb_allocator {int /*<<< orphan*/  lock; } ;
struct iwl_trans_pcie {struct iwl_rxq* rxq; struct iwl_rb_allocator rba; } ;
struct iwl_trans {int num_rx_queues; } ;
struct iwl_rxq {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 scalar_t__ WARN_ON (struct iwl_rxq*) ; 
 int iwl_pcie_alloc_rxq_dma (struct iwl_trans*,struct iwl_rxq*) ; 
 struct iwl_rxq* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_pcie_rx_alloc(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_rb_allocator *rba = &trans_pcie->rba;
	int i, ret;

	if (WARN_ON(trans_pcie->rxq))
		return -EINVAL;

	trans_pcie->rxq = kcalloc(trans->num_rx_queues, sizeof(struct iwl_rxq),
				  GFP_KERNEL);
	if (!trans_pcie->rxq)
		return -EINVAL;

	spin_lock_init(&rba->lock);

	for (i = 0; i < trans->num_rx_queues; i++) {
		struct iwl_rxq *rxq = &trans_pcie->rxq[i];

		ret = iwl_pcie_alloc_rxq_dma(trans, rxq);
		if (ret)
			return ret;
	}
	return 0;
}