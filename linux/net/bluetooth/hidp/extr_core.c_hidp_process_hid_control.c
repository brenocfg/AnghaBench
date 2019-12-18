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
struct hidp_session {int /*<<< orphan*/  intr_transmit; int /*<<< orphan*/  ctrl_transmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hidp_session*,unsigned char) ; 
 unsigned char HIDP_CTRL_VIRTUAL_CABLE_UNPLUG ; 
 int /*<<< orphan*/  hidp_session_terminate (struct hidp_session*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hidp_process_hid_control(struct hidp_session *session,
					unsigned char param)
{
	BT_DBG("session %p param 0x%02x", session, param);

	if (param == HIDP_CTRL_VIRTUAL_CABLE_UNPLUG) {
		/* Flush the transmit queues */
		skb_queue_purge(&session->ctrl_transmit);
		skb_queue_purge(&session->intr_transmit);

		hidp_session_terminate(session);
	}
}