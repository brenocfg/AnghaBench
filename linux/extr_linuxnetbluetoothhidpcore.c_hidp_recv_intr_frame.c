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
struct sk_buff {unsigned char len; unsigned char* data; } ;
struct hidp_session {scalar_t__ hid; scalar_t__ input; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 unsigned char HIDP_DATA_RTYPE_INPUT ; 
 unsigned char HIDP_TRANS_DATA ; 
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 int /*<<< orphan*/  hidp_input_report (struct hidp_session*,struct sk_buff*) ; 
 int /*<<< orphan*/  hidp_process_report (struct hidp_session*,int /*<<< orphan*/ ,unsigned char*,unsigned char,int) ; 
 int /*<<< orphan*/  hidp_set_timer (struct hidp_session*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static void hidp_recv_intr_frame(struct hidp_session *session,
				struct sk_buff *skb)
{
	unsigned char hdr;

	BT_DBG("session %p skb %p len %d", session, skb, skb->len);

	hdr = skb->data[0];
	skb_pull(skb, 1);

	if (hdr == (HIDP_TRANS_DATA | HIDP_DATA_RTYPE_INPUT)) {
		hidp_set_timer(session);

		if (session->input)
			hidp_input_report(session, skb);

		if (session->hid) {
			hidp_process_report(session, HID_INPUT_REPORT,
					    skb->data, skb->len, 1);
			BT_DBG("report len %d", skb->len);
		}
	} else {
		BT_DBG("Unsupported protocol header 0x%02x", hdr);
	}

	kfree_skb(skb);
}