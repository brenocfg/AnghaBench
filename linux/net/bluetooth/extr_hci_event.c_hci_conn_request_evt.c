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
struct TYPE_2__ {int /*<<< orphan*/  dev_class; } ;
struct inquiry_entry {TYPE_1__ data; } ;
struct hci_ev_conn_request {scalar_t__ link_type; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  dev_class; } ;
struct hci_dev {int link_mode; int voice_setting; int /*<<< orphan*/  whitelist; int /*<<< orphan*/  blacklist; int /*<<< orphan*/  name; } ;
struct hci_cp_accept_sync_conn_req {int role; int retrans_effort; void* content_format; void* max_latency; void* rx_bandwidth; void* tx_bandwidth; void* pkt_type; int /*<<< orphan*/  bdaddr; } ;
struct hci_cp_accept_conn_req {int role; int retrans_effort; void* content_format; void* max_latency; void* rx_bandwidth; void* tx_bandwidth; void* pkt_type; int /*<<< orphan*/  bdaddr; } ;
struct hci_conn {int pkt_type; void* state; int /*<<< orphan*/  dev_class; } ;
typedef  int /*<<< orphan*/  cp ;
typedef  int __u8 ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 int /*<<< orphan*/  BDADDR_BREDR ; 
 void* BT_CONNECT ; 
 void* BT_CONNECT2 ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  HCI_CONNECTABLE ; 
 int HCI_LM_ACCEPT ; 
 int HCI_LM_MASTER ; 
 int /*<<< orphan*/  HCI_MGMT ; 
 int /*<<< orphan*/  HCI_OP_ACCEPT_CONN_REQ ; 
 int /*<<< orphan*/  HCI_OP_ACCEPT_SYNC_CONN_REQ ; 
 int HCI_PROTO_DEFER ; 
 int /*<<< orphan*/  HCI_ROLE_SLAVE ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ hci_bdaddr_list_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_conn_add (struct hci_dev*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_connect_cfm (struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct inquiry_entry* hci_inquiry_cache_lookup (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int hci_proto_connect_ind (struct hci_dev*,int /*<<< orphan*/ *,scalar_t__,int*) ; 
 int /*<<< orphan*/  hci_reject_conn (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_accept_sync_conn_req*) ; 
 int /*<<< orphan*/  lmp_esco_capable (struct hci_dev*) ; 
 scalar_t__ lmp_rswitch_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hci_conn_request_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_conn_request *ev = (void *) skb->data;
	int mask = hdev->link_mode;
	struct inquiry_entry *ie;
	struct hci_conn *conn;
	__u8 flags = 0;

	BT_DBG("%s bdaddr %pMR type 0x%x", hdev->name, &ev->bdaddr,
	       ev->link_type);

	mask |= hci_proto_connect_ind(hdev, &ev->bdaddr, ev->link_type,
				      &flags);

	if (!(mask & HCI_LM_ACCEPT)) {
		hci_reject_conn(hdev, &ev->bdaddr);
		return;
	}

	if (hci_bdaddr_list_lookup(&hdev->blacklist, &ev->bdaddr,
				   BDADDR_BREDR)) {
		hci_reject_conn(hdev, &ev->bdaddr);
		return;
	}

	/* Require HCI_CONNECTABLE or a whitelist entry to accept the
	 * connection. These features are only touched through mgmt so
	 * only do the checks if HCI_MGMT is set.
	 */
	if (hci_dev_test_flag(hdev, HCI_MGMT) &&
	    !hci_dev_test_flag(hdev, HCI_CONNECTABLE) &&
	    !hci_bdaddr_list_lookup(&hdev->whitelist, &ev->bdaddr,
				    BDADDR_BREDR)) {
		    hci_reject_conn(hdev, &ev->bdaddr);
		    return;
	}

	/* Connection accepted */

	hci_dev_lock(hdev);

	ie = hci_inquiry_cache_lookup(hdev, &ev->bdaddr);
	if (ie)
		memcpy(ie->data.dev_class, ev->dev_class, 3);

	conn = hci_conn_hash_lookup_ba(hdev, ev->link_type,
			&ev->bdaddr);
	if (!conn) {
		conn = hci_conn_add(hdev, ev->link_type, &ev->bdaddr,
				    HCI_ROLE_SLAVE);
		if (!conn) {
			bt_dev_err(hdev, "no memory for new connection");
			hci_dev_unlock(hdev);
			return;
		}
	}

	memcpy(conn->dev_class, ev->dev_class, 3);

	hci_dev_unlock(hdev);

	if (ev->link_type == ACL_LINK ||
	    (!(flags & HCI_PROTO_DEFER) && !lmp_esco_capable(hdev))) {
		struct hci_cp_accept_conn_req cp;
		conn->state = BT_CONNECT;

		bacpy(&cp.bdaddr, &ev->bdaddr);

		if (lmp_rswitch_capable(hdev) && (mask & HCI_LM_MASTER))
			cp.role = 0x00; /* Become master */
		else
			cp.role = 0x01; /* Remain slave */

		hci_send_cmd(hdev, HCI_OP_ACCEPT_CONN_REQ, sizeof(cp), &cp);
	} else if (!(flags & HCI_PROTO_DEFER)) {
		struct hci_cp_accept_sync_conn_req cp;
		conn->state = BT_CONNECT;

		bacpy(&cp.bdaddr, &ev->bdaddr);
		cp.pkt_type = cpu_to_le16(conn->pkt_type);

		cp.tx_bandwidth   = cpu_to_le32(0x00001f40);
		cp.rx_bandwidth   = cpu_to_le32(0x00001f40);
		cp.max_latency    = cpu_to_le16(0xffff);
		cp.content_format = cpu_to_le16(hdev->voice_setting);
		cp.retrans_effort = 0xff;

		hci_send_cmd(hdev, HCI_OP_ACCEPT_SYNC_CONN_REQ, sizeof(cp),
			     &cp);
	} else {
		conn->state = BT_CONNECT2;
		hci_connect_cfm(conn, 0);
	}
}