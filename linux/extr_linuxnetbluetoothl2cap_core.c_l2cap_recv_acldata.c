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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct l2cap_hdr {int /*<<< orphan*/  len; } ;
struct l2cap_conn {int rx_len; struct sk_buff* rx_skb; } ;
struct hci_conn {TYPE_1__* hdev; struct l2cap_conn* l2cap_data; } ;
struct TYPE_2__ {scalar_t__ dev_type; } ;

/* Variables and functions */
#define  ACL_COMPLETE 131 
#define  ACL_CONT 130 
#define  ACL_START 129 
#define  ACL_START_NO_FLUSH 128 
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  BT_ERR (char*,int,...) ; 
 int /*<<< orphan*/  ECOMM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HCI_PRIMARY ; 
 int L2CAP_HDR_SIZE ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct sk_buff* bt_skb_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct l2cap_conn* l2cap_conn_add (struct hci_conn*) ; 
 int /*<<< orphan*/  l2cap_conn_unreliable (struct l2cap_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_recv_frame (struct l2cap_conn*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

void l2cap_recv_acldata(struct hci_conn *hcon, struct sk_buff *skb, u16 flags)
{
	struct l2cap_conn *conn = hcon->l2cap_data;
	struct l2cap_hdr *hdr;
	int len;

	/* For AMP controller do not create l2cap conn */
	if (!conn && hcon->hdev->dev_type != HCI_PRIMARY)
		goto drop;

	if (!conn)
		conn = l2cap_conn_add(hcon);

	if (!conn)
		goto drop;

	BT_DBG("conn %p len %d flags 0x%x", conn, skb->len, flags);

	switch (flags) {
	case ACL_START:
	case ACL_START_NO_FLUSH:
	case ACL_COMPLETE:
		if (conn->rx_len) {
			BT_ERR("Unexpected start frame (len %d)", skb->len);
			kfree_skb(conn->rx_skb);
			conn->rx_skb = NULL;
			conn->rx_len = 0;
			l2cap_conn_unreliable(conn, ECOMM);
		}

		/* Start fragment always begin with Basic L2CAP header */
		if (skb->len < L2CAP_HDR_SIZE) {
			BT_ERR("Frame is too short (len %d)", skb->len);
			l2cap_conn_unreliable(conn, ECOMM);
			goto drop;
		}

		hdr = (struct l2cap_hdr *) skb->data;
		len = __le16_to_cpu(hdr->len) + L2CAP_HDR_SIZE;

		if (len == skb->len) {
			/* Complete frame received */
			l2cap_recv_frame(conn, skb);
			return;
		}

		BT_DBG("Start: total len %d, frag len %d", len, skb->len);

		if (skb->len > len) {
			BT_ERR("Frame is too long (len %d, expected len %d)",
			       skb->len, len);
			l2cap_conn_unreliable(conn, ECOMM);
			goto drop;
		}

		/* Allocate skb for the complete frame (with header) */
		conn->rx_skb = bt_skb_alloc(len, GFP_KERNEL);
		if (!conn->rx_skb)
			goto drop;

		skb_copy_from_linear_data(skb, skb_put(conn->rx_skb, skb->len),
					  skb->len);
		conn->rx_len = len - skb->len;
		break;

	case ACL_CONT:
		BT_DBG("Cont: frag len %d (expecting %d)", skb->len, conn->rx_len);

		if (!conn->rx_len) {
			BT_ERR("Unexpected continuation frame (len %d)", skb->len);
			l2cap_conn_unreliable(conn, ECOMM);
			goto drop;
		}

		if (skb->len > conn->rx_len) {
			BT_ERR("Fragment is too long (len %d, expected %d)",
			       skb->len, conn->rx_len);
			kfree_skb(conn->rx_skb);
			conn->rx_skb = NULL;
			conn->rx_len = 0;
			l2cap_conn_unreliable(conn, ECOMM);
			goto drop;
		}

		skb_copy_from_linear_data(skb, skb_put(conn->rx_skb, skb->len),
					  skb->len);
		conn->rx_len -= skb->len;

		if (!conn->rx_len) {
			/* Complete frame received. l2cap_recv_frame
			 * takes ownership of the skb so set the global
			 * rx_skb pointer to NULL first.
			 */
			struct sk_buff *rx_skb = conn->rx_skb;
			conn->rx_skb = NULL;
			l2cap_recv_frame(conn, rx_skb);
		}
		break;
	}

drop:
	kfree_skb(skb);
}