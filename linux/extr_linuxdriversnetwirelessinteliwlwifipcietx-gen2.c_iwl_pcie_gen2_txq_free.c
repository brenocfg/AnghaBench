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
struct iwl_txq {int n_window; int /*<<< orphan*/  stuck_timer; TYPE_1__* entries; } ;
struct iwl_trans_pcie {int cmd_queue; int /*<<< orphan*/  queue_used; struct iwl_txq** txq; } ;
struct iwl_trans {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  free_buf; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_pcie_gen2_txq_free_memory (struct iwl_trans*,struct iwl_txq*) ; 
 int /*<<< orphan*/  iwl_pcie_gen2_txq_unmap (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_pcie_gen2_txq_free(struct iwl_trans *trans, int txq_id)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_txq *txq = trans_pcie->txq[txq_id];
	int i;

	if (WARN_ON(!txq))
		return;

	iwl_pcie_gen2_txq_unmap(trans, txq_id);

	/* De-alloc array of command/tx buffers */
	if (txq_id == trans_pcie->cmd_queue)
		for (i = 0; i < txq->n_window; i++) {
			kzfree(txq->entries[i].cmd);
			kzfree(txq->entries[i].free_buf);
		}
	del_timer_sync(&txq->stuck_timer);

	iwl_pcie_gen2_txq_free_memory(trans, txq);

	trans_pcie->txq[txq_id] = NULL;

	clear_bit(txq_id, trans_pcie->queue_used);
}