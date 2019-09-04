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
typedef  int /*<<< orphan*/  u16 ;
struct mgmt_pending_cmd {int /*<<< orphan*/  (* cmd_complete ) (struct mgmt_pending_cmd*,int /*<<< orphan*/ ) ;} ;
struct hci_dev {int dummy; } ;
struct hci_cp_read_rssi {int /*<<< orphan*/  handle; } ;
struct hci_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_OP_READ_RSSI ; 
 int /*<<< orphan*/  HCI_OP_READ_TX_POWER ; 
 int /*<<< orphan*/  MGMT_OP_GET_CONN_INFO ; 
 int /*<<< orphan*/  MGMT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,...) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct hci_cp_read_rssi* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  mgmt_status (int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* pending_find_data (int /*<<< orphan*/ ,struct hci_dev*,struct hci_conn*) ; 
 int /*<<< orphan*/  stub1 (struct mgmt_pending_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void conn_info_refresh_complete(struct hci_dev *hdev, u8 hci_status,
				       u16 opcode)
{
	struct hci_cp_read_rssi *cp;
	struct mgmt_pending_cmd *cmd;
	struct hci_conn *conn;
	u16 handle;
	u8 status;

	BT_DBG("status 0x%02x", hci_status);

	hci_dev_lock(hdev);

	/* Commands sent in request are either Read RSSI or Read Transmit Power
	 * Level so we check which one was last sent to retrieve connection
	 * handle.  Both commands have handle as first parameter so it's safe to
	 * cast data on the same command struct.
	 *
	 * First command sent is always Read RSSI and we fail only if it fails.
	 * In other case we simply override error to indicate success as we
	 * already remembered if TX power value is actually valid.
	 */
	cp = hci_sent_cmd_data(hdev, HCI_OP_READ_RSSI);
	if (!cp) {
		cp = hci_sent_cmd_data(hdev, HCI_OP_READ_TX_POWER);
		status = MGMT_STATUS_SUCCESS;
	} else {
		status = mgmt_status(hci_status);
	}

	if (!cp) {
		bt_dev_err(hdev, "invalid sent_cmd in conn_info response");
		goto unlock;
	}

	handle = __le16_to_cpu(cp->handle);
	conn = hci_conn_hash_lookup_handle(hdev, handle);
	if (!conn) {
		bt_dev_err(hdev, "unknown handle (%d) in conn_info response",
			   handle);
		goto unlock;
	}

	cmd = pending_find_data(MGMT_OP_GET_CONN_INFO, hdev, conn);
	if (!cmd)
		goto unlock;

	cmd->cmd_complete(cmd, status);
	mgmt_pending_remove(cmd);

unlock:
	hci_dev_unlock(hdev);
}