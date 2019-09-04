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
struct hci_conn {scalar_t__ key_type; int /*<<< orphan*/  flags; int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*) ; 
 int /*<<< orphan*/  HCI_CONN_AES_CCM ; 
 int /*<<< orphan*/  HCI_CONN_ENCRYPT ; 
 scalar_t__ HCI_LK_AUTH_COMBINATION_P256 ; 
 int /*<<< orphan*/  HCI_SC_ONLY ; 
 int /*<<< orphan*/  hci_conn_sc_enabled (struct hci_conn*) ; 
 scalar_t__ hci_conn_ssp_enabled (struct hci_conn*) ; 
 scalar_t__ hci_dev_test_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hci_conn_check_link_mode(struct hci_conn *conn)
{
	BT_DBG("hcon %p", conn);

	/* In Secure Connections Only mode, it is required that Secure
	 * Connections is used and the link is encrypted with AES-CCM
	 * using a P-256 authenticated combination key.
	 */
	if (hci_dev_test_flag(conn->hdev, HCI_SC_ONLY)) {
		if (!hci_conn_sc_enabled(conn) ||
		    !test_bit(HCI_CONN_AES_CCM, &conn->flags) ||
		    conn->key_type != HCI_LK_AUTH_COMBINATION_P256)
			return 0;
	}

	if (hci_conn_ssp_enabled(conn) &&
	    !test_bit(HCI_CONN_ENCRYPT, &conn->flags))
		return 0;

	return 1;
}