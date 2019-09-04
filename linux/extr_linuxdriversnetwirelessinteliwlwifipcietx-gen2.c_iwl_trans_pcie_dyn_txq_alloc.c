#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct iwlagn_scd_bc_tbl {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  dma; } ;
struct iwl_txq {int id; int read_ptr; int write_ptr; TYPE_4__ bc_tbl; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  wd_timeout; } ;
struct iwl_tx_queue_cfg_rsp {int /*<<< orphan*/  write_pointer; int /*<<< orphan*/  queue_number; } ;
struct iwl_tx_queue_cfg_cmd {int /*<<< orphan*/  cb_size; void* byte_cnt_addr; void* tfdq_addr; } ;
struct iwl_trans_pcie {struct iwl_txq** txq; int /*<<< orphan*/  queue_used; } ;
struct iwl_trans {TYPE_2__* cfg; } ;
struct iwl_host_cmd {int id; TYPE_3__* resp_pkt; int /*<<< orphan*/  flags; int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct iwl_gen3_bc_tbl {int dummy; } ;
struct TYPE_7__ {scalar_t__ data; } ;
struct TYPE_6__ {scalar_t__ device_family; TYPE_1__* base_params; } ;
struct TYPE_5__ {int max_tfd_queue_size; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct iwl_txq**) ; 
 int /*<<< orphan*/  CMD_WANT_SKB ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HBUS_TARG_WRPTR ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_trans*,char*,int) ; 
 scalar_t__ IWL_DEVICE_FAMILY_22560 ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  TFD_QUEUE_CB_SIZE (int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_free_resp (struct iwl_host_cmd*) ; 
 int iwl_pcie_alloc_dma_ptr (struct iwl_trans*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  iwl_pcie_gen2_txq_free_memory (struct iwl_trans*,struct iwl_txq*) ; 
 int iwl_pcie_txq_alloc (struct iwl_trans*,struct iwl_txq*,int,int) ; 
 int iwl_pcie_txq_init (struct iwl_trans*,struct iwl_txq*,int,int) ; 
 int iwl_rx_packet_payload_len (TYPE_3__*) ; 
 int iwl_trans_send_cmd (struct iwl_trans*,struct iwl_host_cmd*) ; 
 int /*<<< orphan*/  iwl_write_direct32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct iwl_txq*) ; 
 struct iwl_txq* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ ) ; 

int iwl_trans_pcie_dyn_txq_alloc(struct iwl_trans *trans,
				 struct iwl_tx_queue_cfg_cmd *cmd,
				 int cmd_id, int size,
				 unsigned int timeout)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_tx_queue_cfg_rsp *rsp;
	struct iwl_txq *txq;
	struct iwl_host_cmd hcmd = {
		.id = cmd_id,
		.len = { sizeof(*cmd) },
		.data = { cmd, },
		.flags = CMD_WANT_SKB,
	};
	int ret, qid;
	u32 wr_ptr;

	txq = kzalloc(sizeof(*txq), GFP_KERNEL);
	if (!txq)
		return -ENOMEM;
	ret = iwl_pcie_alloc_dma_ptr(trans, &txq->bc_tbl,
				     (trans->cfg->device_family >=
				      IWL_DEVICE_FAMILY_22560) ?
				     sizeof(struct iwl_gen3_bc_tbl) :
				     sizeof(struct iwlagn_scd_bc_tbl));
	if (ret) {
		IWL_ERR(trans, "Scheduler BC Table allocation failed\n");
		kfree(txq);
		return -ENOMEM;
	}

	ret = iwl_pcie_txq_alloc(trans, txq, size, false);
	if (ret) {
		IWL_ERR(trans, "Tx queue alloc failed\n");
		goto error;
	}
	ret = iwl_pcie_txq_init(trans, txq, size, false);
	if (ret) {
		IWL_ERR(trans, "Tx queue init failed\n");
		goto error;
	}

	txq->wd_timeout = msecs_to_jiffies(timeout);

	cmd->tfdq_addr = cpu_to_le64(txq->dma_addr);
	cmd->byte_cnt_addr = cpu_to_le64(txq->bc_tbl.dma);
	cmd->cb_size = cpu_to_le32(TFD_QUEUE_CB_SIZE(size));

	ret = iwl_trans_send_cmd(trans, &hcmd);
	if (ret)
		goto error;

	if (WARN_ON(iwl_rx_packet_payload_len(hcmd.resp_pkt) != sizeof(*rsp))) {
		ret = -EINVAL;
		goto error_free_resp;
	}

	rsp = (void *)hcmd.resp_pkt->data;
	qid = le16_to_cpu(rsp->queue_number);
	wr_ptr = le16_to_cpu(rsp->write_pointer);

	if (qid >= ARRAY_SIZE(trans_pcie->txq)) {
		WARN_ONCE(1, "queue index %d unsupported", qid);
		ret = -EIO;
		goto error_free_resp;
	}

	if (test_and_set_bit(qid, trans_pcie->queue_used)) {
		WARN_ONCE(1, "queue %d already used", qid);
		ret = -EIO;
		goto error_free_resp;
	}

	txq->id = qid;
	trans_pcie->txq[qid] = txq;
	wr_ptr &= (trans->cfg->base_params->max_tfd_queue_size - 1);

	/* Place first TFD at index corresponding to start sequence number */
	txq->read_ptr = wr_ptr;
	txq->write_ptr = wr_ptr;
	iwl_write_direct32(trans, HBUS_TARG_WRPTR,
			   (txq->write_ptr) | (qid << 16));
	IWL_DEBUG_TX_QUEUES(trans, "Activate queue %d\n", qid);

	iwl_free_resp(&hcmd);
	return qid;

error_free_resp:
	iwl_free_resp(&hcmd);
error:
	iwl_pcie_gen2_txq_free_memory(trans, txq);
	return ret;
}