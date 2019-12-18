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
typedef  int /*<<< orphan*/  u16 ;
struct smp_irk {int /*<<< orphan*/  rpa; } ;
struct hci_request {int dummy; } ;
struct hci_dev {scalar_t__ le_scan_type; int /*<<< orphan*/  le_supv_timeout; int /*<<< orphan*/  le_conn_latency; int /*<<< orphan*/  le_conn_max_interval; int /*<<< orphan*/  le_conn_min_interval; } ;
struct hci_conn_params {int /*<<< orphan*/  supervision_timeout; int /*<<< orphan*/  conn_latency; int /*<<< orphan*/  conn_max_interval; int /*<<< orphan*/  conn_min_interval; } ;
struct hci_conn {scalar_t__ role; int /*<<< orphan*/  le_supv_timeout; int /*<<< orphan*/  le_conn_latency; int /*<<< orphan*/  le_conn_max_interval; int /*<<< orphan*/  le_conn_min_interval; void* dst_type; int /*<<< orphan*/  dst; int /*<<< orphan*/  conn_timeout; int /*<<< orphan*/  sec_level; void* pending_sec_level; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  enable ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 void* ADDR_LE_DEV_RANDOM ; 
 int /*<<< orphan*/  BDADDR_ANY ; 
 int /*<<< orphan*/  BT_SECURITY_LOW ; 
 int EBUSY ; 
 int ECONNREFUSED ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 struct hci_conn* ERR_PTR (int) ; 
 int /*<<< orphan*/  HCI_CONN_SCANNING ; 
 int /*<<< orphan*/  HCI_LE_ADV ; 
 int /*<<< orphan*/  HCI_LE_ENABLED ; 
 int /*<<< orphan*/  HCI_LE_SCAN ; 
 int /*<<< orphan*/  HCI_LE_SCAN_INTERRUPTED ; 
 int /*<<< orphan*/  HCI_OP_LE_SET_ADV_ENABLE ; 
 scalar_t__ HCI_ROLE_SLAVE ; 
 int /*<<< orphan*/  LE_LINK ; 
 scalar_t__ LE_SCAN_ACTIVE ; 
 scalar_t__ bacmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_le_conn_complete ; 
 struct hci_conn* hci_conn_add (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  hci_conn_del (struct hci_conn*) ; 
 struct hci_conn* hci_conn_hash_lookup_le (struct hci_dev*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  hci_conn_hold (struct hci_conn*) ; 
 struct hci_conn_params* hci_conn_params_lookup (struct hci_dev*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  hci_dev_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 struct smp_irk* hci_find_irk_by_addr (struct hci_dev*,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ hci_lookup_le_connect (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,void**) ; 
 int /*<<< orphan*/  hci_req_add_le_create_conn (struct hci_request*,struct hci_conn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_req_add_le_scan_disable (struct hci_request*) ; 
 int /*<<< orphan*/  hci_req_directed_advertising (struct hci_request*,struct hci_conn*) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_purge (struct hci_request*) ; 
 int hci_req_run (struct hci_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ lmp_le_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct hci_conn *hci_connect_le(struct hci_dev *hdev, bdaddr_t *dst,
				u8 dst_type, u8 sec_level, u16 conn_timeout,
				u8 role, bdaddr_t *direct_rpa)
{
	struct hci_conn_params *params;
	struct hci_conn *conn;
	struct smp_irk *irk;
	struct hci_request req;
	int err;

	/* Let's make sure that le is enabled.*/
	if (!hci_dev_test_flag(hdev, HCI_LE_ENABLED)) {
		if (lmp_le_capable(hdev))
			return ERR_PTR(-ECONNREFUSED);

		return ERR_PTR(-EOPNOTSUPP);
	}

	/* Since the controller supports only one LE connection attempt at a
	 * time, we return -EBUSY if there is any connection attempt running.
	 */
	if (hci_lookup_le_connect(hdev))
		return ERR_PTR(-EBUSY);

	/* If there's already a connection object but it's not in
	 * scanning state it means it must already be established, in
	 * which case we can't do anything else except report a failure
	 * to connect.
	 */
	conn = hci_conn_hash_lookup_le(hdev, dst, dst_type);
	if (conn && !test_bit(HCI_CONN_SCANNING, &conn->flags)) {
		return ERR_PTR(-EBUSY);
	}

	/* When given an identity address with existing identity
	 * resolving key, the connection needs to be established
	 * to a resolvable random address.
	 *
	 * Storing the resolvable random address is required here
	 * to handle connection failures. The address will later
	 * be resolved back into the original identity address
	 * from the connect request.
	 */
	irk = hci_find_irk_by_addr(hdev, dst, dst_type);
	if (irk && bacmp(&irk->rpa, BDADDR_ANY)) {
		dst = &irk->rpa;
		dst_type = ADDR_LE_DEV_RANDOM;
	}

	if (conn) {
		bacpy(&conn->dst, dst);
	} else {
		conn = hci_conn_add(hdev, LE_LINK, dst, role);
		if (!conn)
			return ERR_PTR(-ENOMEM);
		hci_conn_hold(conn);
		conn->pending_sec_level = sec_level;
	}

	conn->dst_type = dst_type;
	conn->sec_level = BT_SECURITY_LOW;
	conn->conn_timeout = conn_timeout;

	hci_req_init(&req, hdev);

	/* Disable advertising if we're active. For master role
	 * connections most controllers will refuse to connect if
	 * advertising is enabled, and for slave role connections we
	 * anyway have to disable it in order to start directed
	 * advertising.
	 */
	if (hci_dev_test_flag(hdev, HCI_LE_ADV)) {
		u8 enable = 0x00;
		hci_req_add(&req, HCI_OP_LE_SET_ADV_ENABLE, sizeof(enable),
			    &enable);
	}

	/* If requested to connect as slave use directed advertising */
	if (conn->role == HCI_ROLE_SLAVE) {
		/* If we're active scanning most controllers are unable
		 * to initiate advertising. Simply reject the attempt.
		 */
		if (hci_dev_test_flag(hdev, HCI_LE_SCAN) &&
		    hdev->le_scan_type == LE_SCAN_ACTIVE) {
			hci_req_purge(&req);
			hci_conn_del(conn);
			return ERR_PTR(-EBUSY);
		}

		hci_req_directed_advertising(&req, conn);
		goto create_conn;
	}

	params = hci_conn_params_lookup(hdev, &conn->dst, conn->dst_type);
	if (params) {
		conn->le_conn_min_interval = params->conn_min_interval;
		conn->le_conn_max_interval = params->conn_max_interval;
		conn->le_conn_latency = params->conn_latency;
		conn->le_supv_timeout = params->supervision_timeout;
	} else {
		conn->le_conn_min_interval = hdev->le_conn_min_interval;
		conn->le_conn_max_interval = hdev->le_conn_max_interval;
		conn->le_conn_latency = hdev->le_conn_latency;
		conn->le_supv_timeout = hdev->le_supv_timeout;
	}

	/* If controller is scanning, we stop it since some controllers are
	 * not able to scan and connect at the same time. Also set the
	 * HCI_LE_SCAN_INTERRUPTED flag so that the command complete
	 * handler for scan disabling knows to set the correct discovery
	 * state.
	 */
	if (hci_dev_test_flag(hdev, HCI_LE_SCAN)) {
		hci_req_add_le_scan_disable(&req);
		hci_dev_set_flag(hdev, HCI_LE_SCAN_INTERRUPTED);
	}

	hci_req_add_le_create_conn(&req, conn, direct_rpa);

create_conn:
	err = hci_req_run(&req, create_le_conn_complete);
	if (err) {
		hci_conn_del(conn);
		return ERR_PTR(err);
	}

	return conn;
}