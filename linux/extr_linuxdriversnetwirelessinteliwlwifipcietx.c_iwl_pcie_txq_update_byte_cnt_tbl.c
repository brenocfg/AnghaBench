#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct iwlagn_scd_bc_tbl {void** tfd_offset; } ;
struct iwl_txq {int write_ptr; int id; TYPE_2__* entries; } ;
struct iwl_tx_cmd {int sta_id; int sec_ctl; } ;
struct TYPE_6__ {struct iwlagn_scd_bc_tbl* addr; } ;
struct iwl_trans_pcie {scalar_t__ bc_table_dword; TYPE_3__ scd_bc_tbls; } ;
struct iwl_trans {int dummy; } ;
typedef  void* __le16 ;
struct TYPE_5__ {TYPE_1__* cmd; } ;
struct TYPE_4__ {scalar_t__ payload; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int IEEE80211_CCMP_MIC_LEN ; 
 int IEEE80211_TKIP_ICV_LEN ; 
 int IEEE80211_WEP_ICV_LEN ; 
 int IEEE80211_WEP_IV_LEN ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int IWL_TX_CRC_SIZE ; 
 int IWL_TX_DELIMITER_SIZE ; 
 int TFD_QUEUE_SIZE_BC_DUP ; 
 int TFD_QUEUE_SIZE_MAX ; 
#define  TX_CMD_SEC_CCM 130 
 int TX_CMD_SEC_MSK ; 
#define  TX_CMD_SEC_TKIP 129 
#define  TX_CMD_SEC_WEP 128 
 scalar_t__ WARN_ON (int) ; 
 void* cpu_to_le16 (int) ; 

__attribute__((used)) static void iwl_pcie_txq_update_byte_cnt_tbl(struct iwl_trans *trans,
					     struct iwl_txq *txq, u16 byte_cnt,
					     int num_tbs)
{
	struct iwlagn_scd_bc_tbl *scd_bc_tbl;
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	int write_ptr = txq->write_ptr;
	int txq_id = txq->id;
	u8 sec_ctl = 0;
	u16 len = byte_cnt + IWL_TX_CRC_SIZE + IWL_TX_DELIMITER_SIZE;
	__le16 bc_ent;
	struct iwl_tx_cmd *tx_cmd =
		(void *)txq->entries[txq->write_ptr].cmd->payload;
	u8 sta_id = tx_cmd->sta_id;

	scd_bc_tbl = trans_pcie->scd_bc_tbls.addr;

	sec_ctl = tx_cmd->sec_ctl;

	switch (sec_ctl & TX_CMD_SEC_MSK) {
	case TX_CMD_SEC_CCM:
		len += IEEE80211_CCMP_MIC_LEN;
		break;
	case TX_CMD_SEC_TKIP:
		len += IEEE80211_TKIP_ICV_LEN;
		break;
	case TX_CMD_SEC_WEP:
		len += IEEE80211_WEP_IV_LEN + IEEE80211_WEP_ICV_LEN;
		break;
	}
	if (trans_pcie->bc_table_dword)
		len = DIV_ROUND_UP(len, 4);

	if (WARN_ON(len > 0xFFF || write_ptr >= TFD_QUEUE_SIZE_MAX))
		return;

	bc_ent = cpu_to_le16(len | (sta_id << 12));

	scd_bc_tbl[txq_id].tfd_offset[write_ptr] = bc_ent;

	if (write_ptr < TFD_QUEUE_SIZE_BC_DUP)
		scd_bc_tbl[txq_id].
			tfd_offset[TFD_QUEUE_SIZE_MAX + write_ptr] = bc_ent;
}