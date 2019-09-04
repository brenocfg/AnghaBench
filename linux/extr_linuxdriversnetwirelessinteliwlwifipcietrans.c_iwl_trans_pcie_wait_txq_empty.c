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
typedef  scalar_t__ u8 ;
struct iwl_txq {scalar_t__ write_ptr; scalar_t__ read_ptr; } ;
struct iwl_trans_pcie {struct iwl_txq** txq; int /*<<< orphan*/  queue_used; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_trans*,char*,int) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,int) ; 
 int /*<<< orphan*/  IWL_FLUSH_WAIT_MS ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 scalar_t__ READ_ONCE (scalar_t__) ; 
 scalar_t__ WARN_ONCE (int,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iwl_trans_pcie_log_scd_error (struct iwl_trans*,struct iwl_txq*) ; 
 unsigned long jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_after (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int iwl_trans_pcie_wait_txq_empty(struct iwl_trans *trans, int txq_idx)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_txq *txq;
	unsigned long now = jiffies;
	u8 wr_ptr;

	if (!test_bit(txq_idx, trans_pcie->queue_used))
		return -EINVAL;

	IWL_DEBUG_TX_QUEUES(trans, "Emptying queue %d...\n", txq_idx);
	txq = trans_pcie->txq[txq_idx];
	wr_ptr = READ_ONCE(txq->write_ptr);

	while (txq->read_ptr != READ_ONCE(txq->write_ptr) &&
	       !time_after(jiffies,
			   now + msecs_to_jiffies(IWL_FLUSH_WAIT_MS))) {
		u8 write_ptr = READ_ONCE(txq->write_ptr);

		if (WARN_ONCE(wr_ptr != write_ptr,
			      "WR pointer moved while flushing %d -> %d\n",
			      wr_ptr, write_ptr))
			return -ETIMEDOUT;
		usleep_range(1000, 2000);
	}

	if (txq->read_ptr != txq->write_ptr) {
		IWL_ERR(trans,
			"fail to flush all tx fifo queues Q %d\n", txq_idx);
		iwl_trans_pcie_log_scd_error(trans, txq);
		return -ETIMEDOUT;
	}

	IWL_DEBUG_TX_QUEUES(trans, "Queue %d is now empty.\n", txq_idx);

	return 0;
}