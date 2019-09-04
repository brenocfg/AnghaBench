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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct iwl_rxq_sync_cmd {int /*<<< orphan*/  payload; scalar_t__ flags; void* count; void* rxq_mask; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_PATH_GROUP ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IWL_MULTI_QUEUE_SYNC_MSG_MAX_SIZE ; 
 int /*<<< orphan*/  TRIGGER_RX_QUEUES_NOTIF_CMD ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WIDE_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_rxq_sync_cmd*) ; 
 int /*<<< orphan*/  kfree (struct iwl_rxq_sync_cmd*) ; 
 struct iwl_rxq_sync_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

int iwl_mvm_notify_rx_queue(struct iwl_mvm *mvm, u32 rxq_mask,
			    const u8 *data, u32 count)
{
	struct iwl_rxq_sync_cmd *cmd;
	u32 data_size = sizeof(*cmd) + count;
	int ret;

	/* should be DWORD aligned */
	if (WARN_ON(count & 3 || count > IWL_MULTI_QUEUE_SYNC_MSG_MAX_SIZE))
		return -EINVAL;

	cmd = kzalloc(data_size, GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	cmd->rxq_mask = cpu_to_le32(rxq_mask);
	cmd->count =  cpu_to_le32(count);
	cmd->flags = 0;
	memcpy(cmd->payload, data, count);

	ret = iwl_mvm_send_cmd_pdu(mvm,
				   WIDE_ID(DATA_PATH_GROUP,
					   TRIGGER_RX_QUEUES_NOTIF_CMD),
				   0, data_size, cmd);

	kfree(cmd);
	return ret;
}