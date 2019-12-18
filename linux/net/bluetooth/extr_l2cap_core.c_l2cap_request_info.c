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
struct l2cap_info_req {int /*<<< orphan*/  type; } ;
struct l2cap_conn {int info_state; int /*<<< orphan*/  info_ident; int /*<<< orphan*/  info_timer; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int L2CAP_INFO_FEAT_MASK_REQ_SENT ; 
 int /*<<< orphan*/  L2CAP_INFO_REQ ; 
 int /*<<< orphan*/  L2CAP_INFO_TIMEOUT ; 
 int /*<<< orphan*/  L2CAP_IT_FEAT_MASK ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_get_ident (struct l2cap_conn*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_info_req*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_request_info(struct l2cap_conn *conn)
{
	struct l2cap_info_req req;

	if (conn->info_state & L2CAP_INFO_FEAT_MASK_REQ_SENT)
		return;

	req.type = cpu_to_le16(L2CAP_IT_FEAT_MASK);

	conn->info_state |= L2CAP_INFO_FEAT_MASK_REQ_SENT;
	conn->info_ident = l2cap_get_ident(conn);

	schedule_delayed_work(&conn->info_timer, L2CAP_INFO_TIMEOUT);

	l2cap_send_cmd(conn, conn->info_ident, L2CAP_INFO_REQ,
		       sizeof(req), &req);
}