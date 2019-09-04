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
struct mgmt_rp_get_conn_info {void* max_tx_power; void* tx_power; int /*<<< orphan*/  rssi; int /*<<< orphan*/  addr; } ;
struct mgmt_pending_cmd {int /*<<< orphan*/  index; int /*<<< orphan*/  sk; int /*<<< orphan*/  param; struct hci_conn* user_data; } ;
struct hci_conn {void* max_tx_power; void* tx_power; int /*<<< orphan*/  rssi; } ;
typedef  int /*<<< orphan*/  rp ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_RSSI_INVALID ; 
 void* HCI_TX_POWER_INVALID ; 
 int /*<<< orphan*/  MGMT_OP_GET_CONN_INFO ; 
 scalar_t__ MGMT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  hci_conn_drop (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_conn_put (struct hci_conn*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mgmt_cmd_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct mgmt_rp_get_conn_info*,int) ; 

__attribute__((used)) static int conn_info_cmd_complete(struct mgmt_pending_cmd *cmd, u8 status)
{
	struct hci_conn *conn = cmd->user_data;
	struct mgmt_rp_get_conn_info rp;
	int err;

	memcpy(&rp.addr, cmd->param, sizeof(rp.addr));

	if (status == MGMT_STATUS_SUCCESS) {
		rp.rssi = conn->rssi;
		rp.tx_power = conn->tx_power;
		rp.max_tx_power = conn->max_tx_power;
	} else {
		rp.rssi = HCI_RSSI_INVALID;
		rp.tx_power = HCI_TX_POWER_INVALID;
		rp.max_tx_power = HCI_TX_POWER_INVALID;
	}

	err = mgmt_cmd_complete(cmd->sk, cmd->index, MGMT_OP_GET_CONN_INFO,
				status, &rp, sizeof(rp));

	hci_conn_drop(conn);
	hci_conn_put(conn);

	return err;
}