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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  bdaddr; } ;
struct mgmt_rp_unpair_device {TYPE_1__ addr; } ;
struct mgmt_pending_cmd {int /*<<< orphan*/  cmd_complete; } ;
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  bdaddr; } ;
struct mgmt_cp_unpair_device {int disconnect; TYPE_2__ addr; } ;
struct hci_dev {int /*<<< orphan*/  id; } ;
struct hci_conn_params {int /*<<< orphan*/  auto_connect; scalar_t__ explicit_connect; } ;
struct hci_conn {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  rp ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 scalar_t__ BDADDR_BREDR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_AUTO_CONN_DISABLED ; 
 int /*<<< orphan*/  HCI_AUTO_CONN_EXPLICIT ; 
 int /*<<< orphan*/  HCI_CONN_PARAM_REMOVAL_PEND ; 
 int /*<<< orphan*/  HCI_ERROR_REMOTE_USER_TERM ; 
 int /*<<< orphan*/  MGMT_OP_UNPAIR_DEVICE ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_PAIRED ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_POWERED ; 
 int /*<<< orphan*/  addr_cmd_complete ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdaddr_type_is_valid (scalar_t__) ; 
 int /*<<< orphan*/  device_unpaired (struct hci_dev*,int /*<<< orphan*/ *,scalar_t__,struct sock*) ; 
 int hci_abort_conn (struct hci_conn*,int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hci_conn* hci_conn_hash_lookup_le (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_params_del (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hci_conn_params* hci_conn_params_lookup (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int hci_remove_link_key (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdev_is_powered (struct hci_dev*) ; 
 int /*<<< orphan*/  le_addr_type (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct mgmt_rp_unpair_device*,int /*<<< orphan*/ ,int) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mgmt_rp_unpair_device*,int) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,struct mgmt_cp_unpair_device*,int) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int smp_cancel_and_remove_pairing (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unpair_device(struct sock *sk, struct hci_dev *hdev, void *data,
			 u16 len)
{
	struct mgmt_cp_unpair_device *cp = data;
	struct mgmt_rp_unpair_device rp;
	struct hci_conn_params *params;
	struct mgmt_pending_cmd *cmd;
	struct hci_conn *conn;
	u8 addr_type;
	int err;

	memset(&rp, 0, sizeof(rp));
	bacpy(&rp.addr.bdaddr, &cp->addr.bdaddr);
	rp.addr.type = cp->addr.type;

	if (!bdaddr_type_is_valid(cp->addr.type))
		return mgmt_cmd_complete(sk, hdev->id, MGMT_OP_UNPAIR_DEVICE,
					 MGMT_STATUS_INVALID_PARAMS,
					 &rp, sizeof(rp));

	if (cp->disconnect != 0x00 && cp->disconnect != 0x01)
		return mgmt_cmd_complete(sk, hdev->id, MGMT_OP_UNPAIR_DEVICE,
					 MGMT_STATUS_INVALID_PARAMS,
					 &rp, sizeof(rp));

	hci_dev_lock(hdev);

	if (!hdev_is_powered(hdev)) {
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_UNPAIR_DEVICE,
					MGMT_STATUS_NOT_POWERED, &rp,
					sizeof(rp));
		goto unlock;
	}

	if (cp->addr.type == BDADDR_BREDR) {
		/* If disconnection is requested, then look up the
		 * connection. If the remote device is connected, it
		 * will be later used to terminate the link.
		 *
		 * Setting it to NULL explicitly will cause no
		 * termination of the link.
		 */
		if (cp->disconnect)
			conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK,
						       &cp->addr.bdaddr);
		else
			conn = NULL;

		err = hci_remove_link_key(hdev, &cp->addr.bdaddr);
		if (err < 0) {
			err = mgmt_cmd_complete(sk, hdev->id,
						MGMT_OP_UNPAIR_DEVICE,
						MGMT_STATUS_NOT_PAIRED, &rp,
						sizeof(rp));
			goto unlock;
		}

		goto done;
	}

	/* LE address type */
	addr_type = le_addr_type(cp->addr.type);

	/* Abort any ongoing SMP pairing. Removes ltk and irk if they exist. */
	err = smp_cancel_and_remove_pairing(hdev, &cp->addr.bdaddr, addr_type);
	if (err < 0) {
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_UNPAIR_DEVICE,
					MGMT_STATUS_NOT_PAIRED, &rp,
					sizeof(rp));
		goto unlock;
	}

	conn = hci_conn_hash_lookup_le(hdev, &cp->addr.bdaddr, addr_type);
	if (!conn) {
		hci_conn_params_del(hdev, &cp->addr.bdaddr, addr_type);
		goto done;
	}


	/* Defer clearing up the connection parameters until closing to
	 * give a chance of keeping them if a repairing happens.
	 */
	set_bit(HCI_CONN_PARAM_REMOVAL_PEND, &conn->flags);

	/* Disable auto-connection parameters if present */
	params = hci_conn_params_lookup(hdev, &cp->addr.bdaddr, addr_type);
	if (params) {
		if (params->explicit_connect)
			params->auto_connect = HCI_AUTO_CONN_EXPLICIT;
		else
			params->auto_connect = HCI_AUTO_CONN_DISABLED;
	}

	/* If disconnection is not requested, then clear the connection
	 * variable so that the link is not terminated.
	 */
	if (!cp->disconnect)
		conn = NULL;

done:
	/* If the connection variable is set, then termination of the
	 * link is requested.
	 */
	if (!conn) {
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_UNPAIR_DEVICE, 0,
					&rp, sizeof(rp));
		device_unpaired(hdev, &cp->addr.bdaddr, cp->addr.type, sk);
		goto unlock;
	}

	cmd = mgmt_pending_add(sk, MGMT_OP_UNPAIR_DEVICE, hdev, cp,
			       sizeof(*cp));
	if (!cmd) {
		err = -ENOMEM;
		goto unlock;
	}

	cmd->cmd_complete = addr_cmd_complete;

	err = hci_abort_conn(conn, HCI_ERROR_REMOTE_USER_TERM);
	if (err < 0)
		mgmt_pending_remove(cmd);

unlock:
	hci_dev_unlock(hdev);
	return err;
}