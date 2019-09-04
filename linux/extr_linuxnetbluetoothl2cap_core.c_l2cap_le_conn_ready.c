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
struct l2cap_conn_param_update_req {void* to_multiplier; void* latency; void* max; void* min; } ;
struct l2cap_conn {struct hci_conn* hcon; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_conn {scalar_t__ role; scalar_t__ le_conn_interval; scalar_t__ le_conn_min_interval; scalar_t__ le_conn_max_interval; scalar_t__ le_conn_latency; scalar_t__ le_supv_timeout; int /*<<< orphan*/  pending_sec_level; scalar_t__ out; struct hci_dev* hdev; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,struct l2cap_conn*) ; 
 scalar_t__ HCI_ROLE_SLAVE ; 
 int /*<<< orphan*/  L2CAP_CONN_PARAM_UPDATE_REQ ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  l2cap_get_ident (struct l2cap_conn*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_conn_param_update_req*) ; 
 int /*<<< orphan*/  smp_conn_security (struct hci_conn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_le_conn_ready(struct l2cap_conn *conn)
{
	struct hci_conn *hcon = conn->hcon;
	struct hci_dev *hdev = hcon->hdev;

	BT_DBG("%s conn %p", hdev->name, conn);

	/* For outgoing pairing which doesn't necessarily have an
	 * associated socket (e.g. mgmt_pair_device).
	 */
	if (hcon->out)
		smp_conn_security(hcon, hcon->pending_sec_level);

	/* For LE slave connections, make sure the connection interval
	 * is in the range of the minium and maximum interval that has
	 * been configured for this connection. If not, then trigger
	 * the connection update procedure.
	 */
	if (hcon->role == HCI_ROLE_SLAVE &&
	    (hcon->le_conn_interval < hcon->le_conn_min_interval ||
	     hcon->le_conn_interval > hcon->le_conn_max_interval)) {
		struct l2cap_conn_param_update_req req;

		req.min = cpu_to_le16(hcon->le_conn_min_interval);
		req.max = cpu_to_le16(hcon->le_conn_max_interval);
		req.latency = cpu_to_le16(hcon->le_conn_latency);
		req.to_multiplier = cpu_to_le16(hcon->le_supv_timeout);

		l2cap_send_cmd(conn, l2cap_get_ident(conn),
			       L2CAP_CONN_PARAM_UPDATE_REQ, sizeof(req), &req);
	}
}