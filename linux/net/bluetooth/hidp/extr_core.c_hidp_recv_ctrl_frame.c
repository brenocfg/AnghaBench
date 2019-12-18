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
struct sk_buff {unsigned char* data; int /*<<< orphan*/  len; } ;
struct hidp_session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hidp_session*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 unsigned char HIDP_HEADER_PARAM_MASK ; 
 unsigned char HIDP_HEADER_TRANS_MASK ; 
 int const HIDP_HSHK_ERR_UNSUPPORTED_REQUEST ; 
#define  HIDP_TRANS_DATA 130 
#define  HIDP_TRANS_HANDSHAKE 129 
#define  HIDP_TRANS_HID_CONTROL 128 
 int hidp_process_data (struct hidp_session*,struct sk_buff*,unsigned char) ; 
 int /*<<< orphan*/  hidp_process_handshake (struct hidp_session*,unsigned char) ; 
 int /*<<< orphan*/  hidp_process_hid_control (struct hidp_session*,unsigned char) ; 
 int /*<<< orphan*/  hidp_send_ctrl_message (struct hidp_session*,int const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static void hidp_recv_ctrl_frame(struct hidp_session *session,
					struct sk_buff *skb)
{
	unsigned char hdr, type, param;
	int free_skb = 1;

	BT_DBG("session %p skb %p len %d", session, skb, skb->len);

	hdr = skb->data[0];
	skb_pull(skb, 1);

	type = hdr & HIDP_HEADER_TRANS_MASK;
	param = hdr & HIDP_HEADER_PARAM_MASK;

	switch (type) {
	case HIDP_TRANS_HANDSHAKE:
		hidp_process_handshake(session, param);
		break;

	case HIDP_TRANS_HID_CONTROL:
		hidp_process_hid_control(session, param);
		break;

	case HIDP_TRANS_DATA:
		free_skb = hidp_process_data(session, skb, param);
		break;

	default:
		hidp_send_ctrl_message(session,
			HIDP_TRANS_HANDSHAKE | HIDP_HSHK_ERR_UNSUPPORTED_REQUEST, NULL, 0);
		break;
	}

	if (free_skb)
		kfree_skb(skb);
}