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
struct hidp_session {int output_report_success; int /*<<< orphan*/  report_queue; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hidp_session*,unsigned char) ; 
 int const HIDP_CTRL_SOFT_RESET ; 
#define  HIDP_HSHK_ERR_FATAL 134 
#define  HIDP_HSHK_ERR_INVALID_PARAMETER 133 
#define  HIDP_HSHK_ERR_INVALID_REPORT_ID 132 
#define  HIDP_HSHK_ERR_UNKNOWN 131 
#define  HIDP_HSHK_ERR_UNSUPPORTED_REQUEST 130 
#define  HIDP_HSHK_NOT_READY 129 
#define  HIDP_HSHK_SUCCESSFUL 128 
 int const HIDP_TRANS_HANDSHAKE ; 
 int const HIDP_TRANS_HID_CONTROL ; 
 int /*<<< orphan*/  HIDP_WAITING_FOR_RETURN ; 
 int /*<<< orphan*/  HIDP_WAITING_FOR_SEND_ACK ; 
 int /*<<< orphan*/  hidp_send_ctrl_message (struct hidp_session*,int const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hidp_process_handshake(struct hidp_session *session,
					unsigned char param)
{
	BT_DBG("session %p param 0x%02x", session, param);
	session->output_report_success = 0; /* default condition */

	switch (param) {
	case HIDP_HSHK_SUCCESSFUL:
		/* FIXME: Call into SET_ GET_ handlers here */
		session->output_report_success = 1;
		break;

	case HIDP_HSHK_NOT_READY:
	case HIDP_HSHK_ERR_INVALID_REPORT_ID:
	case HIDP_HSHK_ERR_UNSUPPORTED_REQUEST:
	case HIDP_HSHK_ERR_INVALID_PARAMETER:
		if (test_and_clear_bit(HIDP_WAITING_FOR_RETURN, &session->flags))
			wake_up_interruptible(&session->report_queue);

		/* FIXME: Call into SET_ GET_ handlers here */
		break;

	case HIDP_HSHK_ERR_UNKNOWN:
		break;

	case HIDP_HSHK_ERR_FATAL:
		/* Device requests a reboot, as this is the only way this error
		 * can be recovered. */
		hidp_send_ctrl_message(session,
			HIDP_TRANS_HID_CONTROL | HIDP_CTRL_SOFT_RESET, NULL, 0);
		break;

	default:
		hidp_send_ctrl_message(session,
			HIDP_TRANS_HANDSHAKE | HIDP_HSHK_ERR_INVALID_PARAMETER, NULL, 0);
		break;
	}

	/* Wake up the waiting thread. */
	if (test_and_clear_bit(HIDP_WAITING_FOR_SEND_ACK, &session->flags))
		wake_up_interruptible(&session->report_queue);
}