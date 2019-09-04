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
struct iwl_rb_allocator {int /*<<< orphan*/  rx_alloc; } ;
struct iwl_trans_pcie {struct iwl_rxq* rxq; struct iwl_rb_allocator rba; } ;
struct iwl_trans {int num_rx_queues; } ;
struct TYPE_2__ {scalar_t__ poll; } ;
struct iwl_rxq {TYPE_1__ napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_pcie_free_rbs_pool (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_free_rxq_dma (struct iwl_trans*,struct iwl_rxq*) ; 
 int /*<<< orphan*/  kfree (struct iwl_rxq*) ; 
 int /*<<< orphan*/  netif_napi_del (TYPE_1__*) ; 

void iwl_pcie_rx_free(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_rb_allocator *rba = &trans_pcie->rba;
	int i;

	/*
	 * if rxq is NULL, it means that nothing has been allocated,
	 * exit now
	 */
	if (!trans_pcie->rxq) {
		IWL_DEBUG_INFO(trans, "Free NULL rx context\n");
		return;
	}

	cancel_work_sync(&rba->rx_alloc);

	iwl_pcie_free_rbs_pool(trans);

	for (i = 0; i < trans->num_rx_queues; i++) {
		struct iwl_rxq *rxq = &trans_pcie->rxq[i];

		iwl_pcie_free_rxq_dma(trans, rxq);

		if (rxq->napi.poll)
			netif_napi_del(&rxq->napi);
	}
	kfree(trans_pcie->rxq);
}