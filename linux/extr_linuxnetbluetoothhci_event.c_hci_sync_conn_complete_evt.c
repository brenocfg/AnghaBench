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
struct sk_buff {scalar_t__ data; } ;
struct hci_ev_sync_conn_complete {int status; scalar_t__ link_type; int /*<<< orphan*/  handle; int /*<<< orphan*/  bdaddr; } ;
struct hci_dev {int esco_type; int /*<<< orphan*/  name; } ;
struct hci_conn {scalar_t__ type; int pkt_type; int /*<<< orphan*/  state; TYPE_1__* link; int /*<<< orphan*/  out; int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CLOSED ; 
 int /*<<< orphan*/  BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int) ; 
 int EDR_ESCO_MASK ; 
 scalar_t__ ESCO_LINK ; 
 int SCO_ESCO_MASK ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_add_sysfs (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_conn_del (struct hci_conn*) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_connect_cfm (struct hci_conn*,int) ; 
 int /*<<< orphan*/  hci_debugfs_create_conn (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_setup_sync (struct hci_conn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_sync_conn_complete_evt(struct hci_dev *hdev,
				       struct sk_buff *skb)
{
	struct hci_ev_sync_conn_complete *ev = (void *) skb->data;
	struct hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ev->link_type, &ev->bdaddr);
	if (!conn) {
		if (ev->link_type == ESCO_LINK)
			goto unlock;

		/* When the link type in the event indicates SCO connection
		 * and lookup of the connection object fails, then check
		 * if an eSCO connection object exists.
		 *
		 * The core limits the synchronous connections to either
		 * SCO or eSCO. The eSCO connection is preferred and tried
		 * to be setup first and until successfully established,
		 * the link type will be hinted as eSCO.
		 */
		conn = hci_conn_hash_lookup_ba(hdev, ESCO_LINK, &ev->bdaddr);
		if (!conn)
			goto unlock;
	}

	switch (ev->status) {
	case 0x00:
		conn->handle = __le16_to_cpu(ev->handle);
		conn->state  = BT_CONNECTED;
		conn->type   = ev->link_type;

		hci_debugfs_create_conn(conn);
		hci_conn_add_sysfs(conn);
		break;

	case 0x10:	/* Connection Accept Timeout */
	case 0x0d:	/* Connection Rejected due to Limited Resources */
	case 0x11:	/* Unsupported Feature or Parameter Value */
	case 0x1c:	/* SCO interval rejected */
	case 0x1a:	/* Unsupported Remote Feature */
	case 0x1f:	/* Unspecified error */
	case 0x20:	/* Unsupported LMP Parameter value */
		if (conn->out) {
			conn->pkt_type = (hdev->esco_type & SCO_ESCO_MASK) |
					(hdev->esco_type & EDR_ESCO_MASK);
			if (hci_setup_sync(conn, conn->link->handle))
				goto unlock;
		}
		/* fall through */

	default:
		conn->state = BT_CLOSED;
		break;
	}

	hci_connect_cfm(conn, ev->status);
	if (ev->status)
		hci_conn_del(conn);

unlock:
	hci_dev_unlock(hdev);
}