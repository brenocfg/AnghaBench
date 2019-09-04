#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct iwl_txfifo_flush_cmd_v3 {int /*<<< orphan*/  queue_control; int /*<<< orphan*/  flush_control; } ;
struct iwl_txfifo_flush_cmd_v2 {int /*<<< orphan*/  queue_control; int /*<<< orphan*/  flush_control; } ;
struct iwl_priv {scalar_t__ valid_contexts; TYPE_2__* fw; TYPE_1__* nvm_data; } ;
typedef  int /*<<< orphan*/  flush_cmd_v3 ;
typedef  int /*<<< orphan*/  flush_cmd_v2 ;
struct TYPE_4__ {int /*<<< orphan*/  ucode_ver; } ;
struct TYPE_3__ {scalar_t__ sku_cap_11n_enable; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int IWL_AGG_TX_QUEUE_MSK ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*,int) ; 
 int /*<<< orphan*/  IWL_DROP_ALL ; 
 int IWL_PAN_SCD_BE_MSK ; 
 int IWL_PAN_SCD_BK_MSK ; 
 int IWL_PAN_SCD_MGMT_MSK ; 
 int IWL_PAN_SCD_MULTICAST_MSK ; 
 int IWL_PAN_SCD_VI_MSK ; 
 int IWL_PAN_SCD_VO_MSK ; 
 int /*<<< orphan*/  IWL_RXON_CTX_BSS ; 
 int IWL_SCD_BE_MSK ; 
 int IWL_SCD_BK_MSK ; 
 int IWL_SCD_MGMT_MSK ; 
 int IWL_SCD_VI_MSK ; 
 int IWL_SCD_VO_MSK ; 
 int IWL_UCODE_API (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REPLY_TXFIFO_FLUSH ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int iwl_dvm_send_cmd_pdu (struct iwl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_txfifo_flush_cmd_v3*) ; 

int iwlagn_txfifo_flush(struct iwl_priv *priv, u32 scd_q_msk)
{
	struct iwl_txfifo_flush_cmd_v3 flush_cmd_v3 = {
		.flush_control = cpu_to_le16(IWL_DROP_ALL),
	};
	struct iwl_txfifo_flush_cmd_v2 flush_cmd_v2 = {
		.flush_control = cpu_to_le16(IWL_DROP_ALL),
	};

	u32 queue_control = IWL_SCD_VO_MSK | IWL_SCD_VI_MSK |
			    IWL_SCD_BE_MSK | IWL_SCD_BK_MSK | IWL_SCD_MGMT_MSK;

	if ((priv->valid_contexts != BIT(IWL_RXON_CTX_BSS)))
		queue_control |= IWL_PAN_SCD_VO_MSK | IWL_PAN_SCD_VI_MSK |
				 IWL_PAN_SCD_BE_MSK | IWL_PAN_SCD_BK_MSK |
				 IWL_PAN_SCD_MGMT_MSK |
				 IWL_PAN_SCD_MULTICAST_MSK;

	if (priv->nvm_data->sku_cap_11n_enable)
		queue_control |= IWL_AGG_TX_QUEUE_MSK;

	if (scd_q_msk)
		queue_control = scd_q_msk;

	IWL_DEBUG_INFO(priv, "queue control: 0x%x\n", queue_control);
	flush_cmd_v3.queue_control = cpu_to_le32(queue_control);
	flush_cmd_v2.queue_control = cpu_to_le16((u16)queue_control);

	if (IWL_UCODE_API(priv->fw->ucode_ver) > 2)
		return iwl_dvm_send_cmd_pdu(priv, REPLY_TXFIFO_FLUSH, 0,
					    sizeof(flush_cmd_v3),
					    &flush_cmd_v3);
	return iwl_dvm_send_cmd_pdu(priv, REPLY_TXFIFO_FLUSH, 0,
				    sizeof(flush_cmd_v2), &flush_cmd_v2);
}