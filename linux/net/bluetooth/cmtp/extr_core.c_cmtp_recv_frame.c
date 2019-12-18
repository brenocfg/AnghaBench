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
struct sk_buff {scalar_t__ len; int* data; } ;
struct cmtp_session {struct sk_buff** reassembly; } ;
typedef  int __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  cmtp_add_msgpart (struct cmtp_session*,int,int*,int) ; 
 int /*<<< orphan*/  cmtp_recv_capimsg (struct cmtp_session*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static inline int cmtp_recv_frame(struct cmtp_session *session, struct sk_buff *skb)
{
	__u8 hdr, hdrlen, id;
	__u16 len;

	BT_DBG("session %p skb %p len %d", session, skb, skb->len);

	while (skb->len > 0) {
		hdr = skb->data[0];

		switch (hdr & 0xc0) {
		case 0x40:
			hdrlen = 2;
			len = skb->data[1];
			break;
		case 0x80:
			hdrlen = 3;
			len = skb->data[1] | (skb->data[2] << 8);
			break;
		default:
			hdrlen = 1;
			len = 0;
			break;
		}

		id = (hdr & 0x3c) >> 2;

		BT_DBG("hdr 0x%02x hdrlen %d len %d id %d", hdr, hdrlen, len, id);

		if (hdrlen + len > skb->len) {
			BT_ERR("Wrong size or header information in CMTP frame");
			break;
		}

		if (len == 0) {
			skb_pull(skb, hdrlen);
			continue;
		}

		switch (hdr & 0x03) {
		case 0x00:
			cmtp_add_msgpart(session, id, skb->data + hdrlen, len);
			cmtp_recv_capimsg(session, session->reassembly[id]);
			session->reassembly[id] = NULL;
			break;
		case 0x01:
			cmtp_add_msgpart(session, id, skb->data + hdrlen, len);
			break;
		default:
			kfree_skb(session->reassembly[id]);
			session->reassembly[id] = NULL;
			break;
		}

		skb_pull(skb, hdrlen + len);
	}

	kfree_skb(skb);
	return 0;
}