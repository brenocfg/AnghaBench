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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct l2cap_hdr {int /*<<< orphan*/  len; int /*<<< orphan*/  cid; } ;
struct l2cap_conn {int /*<<< orphan*/  pending_rx; struct hci_conn* hcon; } ;
struct hci_conn {scalar_t__ state; scalar_t__ type; int /*<<< orphan*/  dst; TYPE_1__* hdev; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  blacklist; } ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
#define  L2CAP_CID_CONN_LESS 130 
#define  L2CAP_CID_LE_SIGNALING 129 
#define  L2CAP_CID_SIGNALING 128 
 int /*<<< orphan*/  L2CAP_HDR_SIZE ; 
 int /*<<< orphan*/  L2CAP_PSMLEN_SIZE ; 
 scalar_t__ LE_LINK ; 
 scalar_t__ __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdaddr_dst_type (struct hci_conn*) ; 
 int /*<<< orphan*/  get_unaligned (int /*<<< orphan*/ *) ; 
 scalar_t__ hci_bdaddr_list_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  l2cap_conless_channel (struct l2cap_conn*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  l2cap_data_channel (struct l2cap_conn*,scalar_t__,struct sk_buff*) ; 
 int /*<<< orphan*/  l2cap_le_sig_channel (struct l2cap_conn*,struct sk_buff*) ; 
 int /*<<< orphan*/  l2cap_sig_channel (struct l2cap_conn*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void l2cap_recv_frame(struct l2cap_conn *conn, struct sk_buff *skb)
{
	struct l2cap_hdr *lh = (void *) skb->data;
	struct hci_conn *hcon = conn->hcon;
	u16 cid, len;
	__le16 psm;

	if (hcon->state != BT_CONNECTED) {
		BT_DBG("queueing pending rx skb");
		skb_queue_tail(&conn->pending_rx, skb);
		return;
	}

	skb_pull(skb, L2CAP_HDR_SIZE);
	cid = __le16_to_cpu(lh->cid);
	len = __le16_to_cpu(lh->len);

	if (len != skb->len) {
		kfree_skb(skb);
		return;
	}

	/* Since we can't actively block incoming LE connections we must
	 * at least ensure that we ignore incoming data from them.
	 */
	if (hcon->type == LE_LINK &&
	    hci_bdaddr_list_lookup(&hcon->hdev->blacklist, &hcon->dst,
				   bdaddr_dst_type(hcon))) {
		kfree_skb(skb);
		return;
	}

	BT_DBG("len %d, cid 0x%4.4x", len, cid);

	switch (cid) {
	case L2CAP_CID_SIGNALING:
		l2cap_sig_channel(conn, skb);
		break;

	case L2CAP_CID_CONN_LESS:
		psm = get_unaligned((__le16 *) skb->data);
		skb_pull(skb, L2CAP_PSMLEN_SIZE);
		l2cap_conless_channel(conn, psm, skb);
		break;

	case L2CAP_CID_LE_SIGNALING:
		l2cap_le_sig_channel(conn, skb);
		break;

	default:
		l2cap_data_channel(conn, cid, skb);
		break;
	}
}