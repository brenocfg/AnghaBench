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
typedef  scalar_t__ u16 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct mgmt_rp_read_local_oob_data {int /*<<< orphan*/  rand256; int /*<<< orphan*/  hash256; int /*<<< orphan*/  rand192; int /*<<< orphan*/  hash192; } ;
struct mgmt_pending_cmd {int /*<<< orphan*/  sk; } ;
struct hci_rp_read_local_oob_ext_data {int /*<<< orphan*/  rand256; int /*<<< orphan*/  hash256; int /*<<< orphan*/  rand192; int /*<<< orphan*/  hash192; } ;
struct hci_rp_read_local_oob_data {int /*<<< orphan*/  rand; int /*<<< orphan*/  hash; } ;
struct hci_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  mgmt_rp ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ HCI_OP_READ_LOCAL_OOB_DATA ; 
 int /*<<< orphan*/  MGMT_OP_READ_LOCAL_OOB_DATA ; 
 int /*<<< orphan*/  MGMT_STATUS_FAILED ; 
 int /*<<< orphan*/  MGMT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct mgmt_rp_read_local_oob_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mgmt_cmd_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mgmt_rp_read_local_oob_data*,size_t) ; 
 int /*<<< orphan*/  mgmt_cmd_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  mgmt_status (scalar_t__) ; 
 struct mgmt_pending_cmd* pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 

__attribute__((used)) static void read_local_oob_data_complete(struct hci_dev *hdev, u8 status,
				         u16 opcode, struct sk_buff *skb)
{
	struct mgmt_rp_read_local_oob_data mgmt_rp;
	size_t rp_size = sizeof(mgmt_rp);
	struct mgmt_pending_cmd *cmd;

	BT_DBG("%s status %u", hdev->name, status);

	cmd = pending_find(MGMT_OP_READ_LOCAL_OOB_DATA, hdev);
	if (!cmd)
		return;

	if (status || !skb) {
		mgmt_cmd_status(cmd->sk, hdev->id, MGMT_OP_READ_LOCAL_OOB_DATA,
				status ? mgmt_status(status) : MGMT_STATUS_FAILED);
		goto remove;
	}

	memset(&mgmt_rp, 0, sizeof(mgmt_rp));

	if (opcode == HCI_OP_READ_LOCAL_OOB_DATA) {
		struct hci_rp_read_local_oob_data *rp = (void *) skb->data;

		if (skb->len < sizeof(*rp)) {
			mgmt_cmd_status(cmd->sk, hdev->id,
					MGMT_OP_READ_LOCAL_OOB_DATA,
					MGMT_STATUS_FAILED);
			goto remove;
		}

		memcpy(mgmt_rp.hash192, rp->hash, sizeof(rp->hash));
		memcpy(mgmt_rp.rand192, rp->rand, sizeof(rp->rand));

		rp_size -= sizeof(mgmt_rp.hash256) + sizeof(mgmt_rp.rand256);
	} else {
		struct hci_rp_read_local_oob_ext_data *rp = (void *) skb->data;

		if (skb->len < sizeof(*rp)) {
			mgmt_cmd_status(cmd->sk, hdev->id,
					MGMT_OP_READ_LOCAL_OOB_DATA,
					MGMT_STATUS_FAILED);
			goto remove;
		}

		memcpy(mgmt_rp.hash192, rp->hash192, sizeof(rp->hash192));
		memcpy(mgmt_rp.rand192, rp->rand192, sizeof(rp->rand192));

		memcpy(mgmt_rp.hash256, rp->hash256, sizeof(rp->hash256));
		memcpy(mgmt_rp.rand256, rp->rand256, sizeof(rp->rand256));
	}

	mgmt_cmd_complete(cmd->sk, hdev->id, MGMT_OP_READ_LOCAL_OOB_DATA,
			  MGMT_STATUS_SUCCESS, &mgmt_rp, rp_size);

remove:
	mgmt_pending_remove(cmd);
}