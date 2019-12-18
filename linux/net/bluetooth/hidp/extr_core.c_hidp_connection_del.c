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
typedef  int u32 ;
struct hidp_session {int /*<<< orphan*/  user; int /*<<< orphan*/  conn; } ;
struct hidp_conndel_req {int flags; int /*<<< orphan*/  bdaddr; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOENT ; 
 int HIDP_CTRL_VIRTUAL_CABLE_UNPLUG ; 
 int HIDP_TRANS_HID_CONTROL ; 
 int /*<<< orphan*/  HIDP_VIRTUAL_CABLE_UNPLUG ; 
 int /*<<< orphan*/  hidp_send_ctrl_message (struct hidp_session*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hidp_session* hidp_session_find (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hidp_session_put (struct hidp_session*) ; 
 int /*<<< orphan*/  l2cap_unregister_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hidp_connection_del(struct hidp_conndel_req *req)
{
	u32 valid_flags = BIT(HIDP_VIRTUAL_CABLE_UNPLUG);
	struct hidp_session *session;

	if (req->flags & ~valid_flags)
		return -EINVAL;

	session = hidp_session_find(&req->bdaddr);
	if (!session)
		return -ENOENT;

	if (req->flags & BIT(HIDP_VIRTUAL_CABLE_UNPLUG))
		hidp_send_ctrl_message(session,
				       HIDP_TRANS_HID_CONTROL |
				         HIDP_CTRL_VIRTUAL_CABLE_UNPLUG,
				       NULL, 0);
	else
		l2cap_unregister_user(session->conn, &session->user);

	hidp_session_put(session);

	return 0;
}