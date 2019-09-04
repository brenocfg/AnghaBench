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
typedef  int u8 ;
typedef  int u16 ;
struct hci_dev {int dummy; } ;
struct hci_cp_le_conn_update {void* max_ce_len; void* min_ce_len; void* supervision_timeout; void* conn_latency; void* conn_interval_max; void* conn_interval_min; void* handle; } ;
struct hci_conn_params {int conn_min_interval; int conn_max_interval; int conn_latency; int supervision_timeout; } ;
struct hci_conn {int handle; int /*<<< orphan*/  dst_type; int /*<<< orphan*/  dst; struct hci_dev* hdev; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_OP_LE_CONN_UPDATE ; 
 void* cpu_to_le16 (int) ; 
 struct hci_conn_params* hci_conn_params_lookup (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_le_conn_update*) ; 
 int /*<<< orphan*/  memset (struct hci_cp_le_conn_update*,int /*<<< orphan*/ ,int) ; 

u8 hci_le_conn_update(struct hci_conn *conn, u16 min, u16 max, u16 latency,
		      u16 to_multiplier)
{
	struct hci_dev *hdev = conn->hdev;
	struct hci_conn_params *params;
	struct hci_cp_le_conn_update cp;

	hci_dev_lock(hdev);

	params = hci_conn_params_lookup(hdev, &conn->dst, conn->dst_type);
	if (params) {
		params->conn_min_interval = min;
		params->conn_max_interval = max;
		params->conn_latency = latency;
		params->supervision_timeout = to_multiplier;
	}

	hci_dev_unlock(hdev);

	memset(&cp, 0, sizeof(cp));
	cp.handle		= cpu_to_le16(conn->handle);
	cp.conn_interval_min	= cpu_to_le16(min);
	cp.conn_interval_max	= cpu_to_le16(max);
	cp.conn_latency		= cpu_to_le16(latency);
	cp.supervision_timeout	= cpu_to_le16(to_multiplier);
	cp.min_ce_len		= cpu_to_le16(0x0000);
	cp.max_ce_len		= cpu_to_le16(0x0000);

	hci_send_cmd(hdev, HCI_OP_LE_CONN_UPDATE, sizeof(cp), &cp);

	if (params)
		return 0x01;

	return 0x00;
}