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
struct sk_buff {scalar_t__* data; int /*<<< orphan*/  len; } ;
struct hidp_session {unsigned char waiting_report_type; scalar_t__ waiting_report_number; int /*<<< orphan*/  report_queue; int /*<<< orphan*/  flags; struct sk_buff* report_return; int /*<<< orphan*/  hid; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hidp_session*,struct sk_buff*,int /*<<< orphan*/ ,unsigned char) ; 
#define  HIDP_DATA_RTYPE_FEATURE 131 
#define  HIDP_DATA_RTYPE_INPUT 130 
#define  HIDP_DATA_RTYPE_OTHER 129 
#define  HIDP_DATA_RTYPE_OUPUT 128 
 int HIDP_HSHK_ERR_INVALID_PARAMETER ; 
 int HIDP_TRANS_HANDSHAKE ; 
 int /*<<< orphan*/  HIDP_WAITING_FOR_RETURN ; 
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hidp_input_report (struct hidp_session*,struct sk_buff*) ; 
 int /*<<< orphan*/  hidp_process_report (struct hidp_session*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hidp_send_ctrl_message (struct hidp_session*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hidp_set_timer (struct hidp_session*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hidp_process_data(struct hidp_session *session, struct sk_buff *skb,
				unsigned char param)
{
	int done_with_skb = 1;
	BT_DBG("session %p skb %p len %d param 0x%02x", session, skb, skb->len, param);

	switch (param) {
	case HIDP_DATA_RTYPE_INPUT:
		hidp_set_timer(session);

		if (session->input)
			hidp_input_report(session, skb);

		if (session->hid)
			hidp_process_report(session, HID_INPUT_REPORT,
					    skb->data, skb->len, 0);
		break;

	case HIDP_DATA_RTYPE_OTHER:
	case HIDP_DATA_RTYPE_OUPUT:
	case HIDP_DATA_RTYPE_FEATURE:
		break;

	default:
		hidp_send_ctrl_message(session,
			HIDP_TRANS_HANDSHAKE | HIDP_HSHK_ERR_INVALID_PARAMETER, NULL, 0);
	}

	if (test_bit(HIDP_WAITING_FOR_RETURN, &session->flags) &&
				param == session->waiting_report_type) {
		if (session->waiting_report_number < 0 ||
		    session->waiting_report_number == skb->data[0]) {
			/* hidp_get_raw_report() is waiting on this report. */
			session->report_return = skb;
			done_with_skb = 0;
			clear_bit(HIDP_WAITING_FOR_RETURN, &session->flags);
			wake_up_interruptible(&session->report_queue);
		}
	}

	return done_with_skb;
}