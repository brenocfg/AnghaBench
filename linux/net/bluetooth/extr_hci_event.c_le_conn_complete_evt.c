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
typedef  void* u8 ;
typedef  void* u16 ;
struct smp_irk {scalar_t__ addr_type; int /*<<< orphan*/  bdaddr; } ;
struct hci_dev {scalar_t__ adv_addr_type; int* le_features; int /*<<< orphan*/  pend_le_conns; int /*<<< orphan*/  blacklist; int /*<<< orphan*/  le_conn_max_interval; int /*<<< orphan*/  le_conn_min_interval; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  random_addr; int /*<<< orphan*/  rpa; } ;
struct hci_cp_le_read_remote_features {int /*<<< orphan*/  handle; } ;
struct hci_conn_params {struct hci_conn* conn; int /*<<< orphan*/  action; } ;
struct hci_conn {scalar_t__ dst_type; scalar_t__ resp_addr_type; int /*<<< orphan*/  dst; int /*<<< orphan*/  state; void* handle; scalar_t__ out; void* le_supv_timeout; void* le_conn_latency; void* le_conn_interval; int /*<<< orphan*/  sec_level; int /*<<< orphan*/  flags; int /*<<< orphan*/  le_conn_max_interval; int /*<<< orphan*/  le_conn_min_interval; int /*<<< orphan*/  init_addr; void* init_addr_type; int /*<<< orphan*/  resp_addr; int /*<<< orphan*/  le_conn_timeout; } ;
typedef  int /*<<< orphan*/  cp ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 scalar_t__ ADDR_LE_DEV_PUBLIC ; 
 scalar_t__ ADDR_LE_DEV_RANDOM ; 
 void* BDADDR_LE_PUBLIC ; 
 void* BDADDR_LE_RANDOM ; 
 int /*<<< orphan*/  BT_CONFIG ; 
 int /*<<< orphan*/  BT_CONNECTED ; 
 int /*<<< orphan*/  BT_SECURITY_LOW ; 
 int /*<<< orphan*/  HCI_CONN_MGMT_CONNECTED ; 
 int /*<<< orphan*/  HCI_LE_ADV ; 
 int HCI_LE_SLAVE_FEATURES ; 
 int /*<<< orphan*/  HCI_OP_LE_READ_REMOTE_FEATURES ; 
 int /*<<< orphan*/  HCI_PRIVACY ; 
 int /*<<< orphan*/  LE_LINK ; 
 int /*<<< orphan*/  __cpu_to_le16 (void*) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext_adv_capable (struct hci_dev*) ; 
 scalar_t__ hci_bdaddr_list_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 struct hci_conn* hci_conn_add (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  hci_conn_add_sysfs (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_conn_drop (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_conn_hold (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_conn_put (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_connect_cfm (struct hci_conn*,void*) ; 
 int /*<<< orphan*/  hci_copy_identity_address (struct hci_dev*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  hci_debugfs_create_conn (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_dev_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct smp_irk* hci_get_irk (struct hci_dev*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  hci_le_conn_failed (struct hci_conn*,void*) ; 
 struct hci_conn* hci_lookup_le_connect (struct hci_dev*) ; 
 struct hci_conn_params* hci_pend_le_action_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_le_read_remote_features*) ; 
 int /*<<< orphan*/  hci_update_background_scan (struct hci_dev*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmt_device_connected (struct hci_dev*,struct hci_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void le_conn_complete_evt(struct hci_dev *hdev, u8 status,
			bdaddr_t *bdaddr, u8 bdaddr_type, u8 role, u16 handle,
			u16 interval, u16 latency, u16 supervision_timeout)
{
	struct hci_conn_params *params;
	struct hci_conn *conn;
	struct smp_irk *irk;
	u8 addr_type;

	hci_dev_lock(hdev);

	/* All controllers implicitly stop advertising in the event of a
	 * connection, so ensure that the state bit is cleared.
	 */
	hci_dev_clear_flag(hdev, HCI_LE_ADV);

	conn = hci_lookup_le_connect(hdev);
	if (!conn) {
		conn = hci_conn_add(hdev, LE_LINK, bdaddr, role);
		if (!conn) {
			bt_dev_err(hdev, "no memory for new connection");
			goto unlock;
		}

		conn->dst_type = bdaddr_type;

		/* If we didn't have a hci_conn object previously
		 * but we're in master role this must be something
		 * initiated using a white list. Since white list based
		 * connections are not "first class citizens" we don't
		 * have full tracking of them. Therefore, we go ahead
		 * with a "best effort" approach of determining the
		 * initiator address based on the HCI_PRIVACY flag.
		 */
		if (conn->out) {
			conn->resp_addr_type = bdaddr_type;
			bacpy(&conn->resp_addr, bdaddr);
			if (hci_dev_test_flag(hdev, HCI_PRIVACY)) {
				conn->init_addr_type = ADDR_LE_DEV_RANDOM;
				bacpy(&conn->init_addr, &hdev->rpa);
			} else {
				hci_copy_identity_address(hdev,
							  &conn->init_addr,
							  &conn->init_addr_type);
			}
		}
	} else {
		cancel_delayed_work(&conn->le_conn_timeout);
	}

	if (!conn->out) {
		/* Set the responder (our side) address type based on
		 * the advertising address type.
		 */
		conn->resp_addr_type = hdev->adv_addr_type;
		if (hdev->adv_addr_type == ADDR_LE_DEV_RANDOM) {
			/* In case of ext adv, resp_addr will be updated in
			 * Adv Terminated event.
			 */
			if (!ext_adv_capable(hdev))
				bacpy(&conn->resp_addr, &hdev->random_addr);
		} else {
			bacpy(&conn->resp_addr, &hdev->bdaddr);
		}

		conn->init_addr_type = bdaddr_type;
		bacpy(&conn->init_addr, bdaddr);

		/* For incoming connections, set the default minimum
		 * and maximum connection interval. They will be used
		 * to check if the parameters are in range and if not
		 * trigger the connection update procedure.
		 */
		conn->le_conn_min_interval = hdev->le_conn_min_interval;
		conn->le_conn_max_interval = hdev->le_conn_max_interval;
	}

	/* Lookup the identity address from the stored connection
	 * address and address type.
	 *
	 * When establishing connections to an identity address, the
	 * connection procedure will store the resolvable random
	 * address first. Now if it can be converted back into the
	 * identity address, start using the identity address from
	 * now on.
	 */
	irk = hci_get_irk(hdev, &conn->dst, conn->dst_type);
	if (irk) {
		bacpy(&conn->dst, &irk->bdaddr);
		conn->dst_type = irk->addr_type;
	}

	if (status) {
		hci_le_conn_failed(conn, status);
		goto unlock;
	}

	if (conn->dst_type == ADDR_LE_DEV_PUBLIC)
		addr_type = BDADDR_LE_PUBLIC;
	else
		addr_type = BDADDR_LE_RANDOM;

	/* Drop the connection if the device is blocked */
	if (hci_bdaddr_list_lookup(&hdev->blacklist, &conn->dst, addr_type)) {
		hci_conn_drop(conn);
		goto unlock;
	}

	if (!test_and_set_bit(HCI_CONN_MGMT_CONNECTED, &conn->flags))
		mgmt_device_connected(hdev, conn, 0, NULL, 0);

	conn->sec_level = BT_SECURITY_LOW;
	conn->handle = handle;
	conn->state = BT_CONFIG;

	conn->le_conn_interval = interval;
	conn->le_conn_latency = latency;
	conn->le_supv_timeout = supervision_timeout;

	hci_debugfs_create_conn(conn);
	hci_conn_add_sysfs(conn);

	/* The remote features procedure is defined for master
	 * role only. So only in case of an initiated connection
	 * request the remote features.
	 *
	 * If the local controller supports slave-initiated features
	 * exchange, then requesting the remote features in slave
	 * role is possible. Otherwise just transition into the
	 * connected state without requesting the remote features.
	 */
	if (conn->out ||
	    (hdev->le_features[0] & HCI_LE_SLAVE_FEATURES)) {
		struct hci_cp_le_read_remote_features cp;

		cp.handle = __cpu_to_le16(conn->handle);

		hci_send_cmd(hdev, HCI_OP_LE_READ_REMOTE_FEATURES,
			     sizeof(cp), &cp);

		hci_conn_hold(conn);
	} else {
		conn->state = BT_CONNECTED;
		hci_connect_cfm(conn, status);
	}

	params = hci_pend_le_action_lookup(&hdev->pend_le_conns, &conn->dst,
					   conn->dst_type);
	if (params) {
		list_del_init(&params->action);
		if (params->conn) {
			hci_conn_drop(params->conn);
			hci_conn_put(params->conn);
			params->conn = NULL;
		}
	}

unlock:
	hci_update_background_scan(hdev);
	hci_dev_unlock(hdev);
}