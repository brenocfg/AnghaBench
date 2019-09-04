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
typedef  int /*<<< orphan*/  u16 ;
struct hci_dev {int dummy; } ;
struct hci_conn {scalar_t__ pending_sec_level; int /*<<< orphan*/  conn_timeout; int /*<<< orphan*/  sec_level; scalar_t__ dst_type; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CONNECT ; 
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  BT_SECURITY_LOW ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ECONNREFUSED ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct hci_conn* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_CONN_SCANNING ; 
 int /*<<< orphan*/  HCI_LE_ENABLED ; 
 int /*<<< orphan*/  HCI_ROLE_MASTER ; 
 int /*<<< orphan*/  LE_LINK ; 
 struct hci_conn* hci_conn_add (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_conn_hash_lookup_le (struct hci_dev*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  hci_conn_hold (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ hci_explicit_conn_params_set (struct hci_dev*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  hci_update_background_scan (struct hci_dev*) ; 
 scalar_t__ lmp_le_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct hci_conn *hci_connect_le_scan(struct hci_dev *hdev, bdaddr_t *dst,
				     u8 dst_type, u8 sec_level,
				     u16 conn_timeout)
{
	struct hci_conn *conn;

	/* Let's make sure that le is enabled.*/
	if (!hci_dev_test_flag(hdev, HCI_LE_ENABLED)) {
		if (lmp_le_capable(hdev))
			return ERR_PTR(-ECONNREFUSED);

		return ERR_PTR(-EOPNOTSUPP);
	}

	/* Some devices send ATT messages as soon as the physical link is
	 * established. To be able to handle these ATT messages, the user-
	 * space first establishes the connection and then starts the pairing
	 * process.
	 *
	 * So if a hci_conn object already exists for the following connection
	 * attempt, we simply update pending_sec_level and auth_type fields
	 * and return the object found.
	 */
	conn = hci_conn_hash_lookup_le(hdev, dst, dst_type);
	if (conn) {
		if (conn->pending_sec_level < sec_level)
			conn->pending_sec_level = sec_level;
		goto done;
	}

	BT_DBG("requesting refresh of dst_addr");

	conn = hci_conn_add(hdev, LE_LINK, dst, HCI_ROLE_MASTER);
	if (!conn)
		return ERR_PTR(-ENOMEM);

	if (hci_explicit_conn_params_set(hdev, dst, dst_type) < 0)
		return ERR_PTR(-EBUSY);

	conn->state = BT_CONNECT;
	set_bit(HCI_CONN_SCANNING, &conn->flags);
	conn->dst_type = dst_type;
	conn->sec_level = BT_SECURITY_LOW;
	conn->pending_sec_level = sec_level;
	conn->conn_timeout = conn_timeout;

	hci_update_background_scan(hdev);

done:
	hci_conn_hold(conn);
	return conn;
}