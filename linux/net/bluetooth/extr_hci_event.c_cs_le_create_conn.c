#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct hci_dev {int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  random_addr; } ;
struct hci_conn {int /*<<< orphan*/  conn_timeout; int /*<<< orphan*/  le_conn_timeout; TYPE_1__* hdev; int /*<<< orphan*/  resp_addr; scalar_t__ resp_addr_type; int /*<<< orphan*/  init_addr; scalar_t__ init_addr_type; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 scalar_t__ ADDR_LE_DEV_RANDOM ; 
 scalar_t__ HCI_LE_USE_PEER_ADDR ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct hci_conn* hci_conn_hash_lookup_le (struct hci_dev*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs_le_create_conn(struct hci_dev *hdev, bdaddr_t *peer_addr,
			      u8 peer_addr_type, u8 own_address_type,
			      u8 filter_policy)
{
	struct hci_conn *conn;

	conn = hci_conn_hash_lookup_le(hdev, peer_addr,
				       peer_addr_type);
	if (!conn)
		return;

	/* Store the initiator and responder address information which
	 * is needed for SMP. These values will not change during the
	 * lifetime of the connection.
	 */
	conn->init_addr_type = own_address_type;
	if (own_address_type == ADDR_LE_DEV_RANDOM)
		bacpy(&conn->init_addr, &hdev->random_addr);
	else
		bacpy(&conn->init_addr, &hdev->bdaddr);

	conn->resp_addr_type = peer_addr_type;
	bacpy(&conn->resp_addr, peer_addr);

	/* We don't want the connection attempt to stick around
	 * indefinitely since LE doesn't have a page timeout concept
	 * like BR/EDR. Set a timer for any connection that doesn't use
	 * the white list for connecting.
	 */
	if (filter_policy == HCI_LE_USE_PEER_ADDR)
		queue_delayed_work(conn->hdev->workqueue,
				   &conn->le_conn_timeout,
				   conn->conn_timeout);
}