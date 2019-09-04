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
struct iwl_trans_pcie {struct iwl_rxq* rxq; } ;
struct iwl_trans {int num_rx_queues; } ;
struct iwl_rxq {int need_update; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_rxq_inc_wr_ptr (struct iwl_trans*,struct iwl_rxq*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_pcie_rxq_check_wrptr(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	int i;

	for (i = 0; i < trans->num_rx_queues; i++) {
		struct iwl_rxq *rxq = &trans_pcie->rxq[i];

		if (!rxq->need_update)
			continue;
		spin_lock(&rxq->lock);
		iwl_pcie_rxq_inc_wr_ptr(trans, rxq);
		rxq->need_update = false;
		spin_unlock(&rxq->lock);
	}
}