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
struct iscsi_task {int dummy; } ;
struct iscsi_session {int cmds_max; struct iscsi_task** cmds; TYPE_1__* tt; } ;
struct iscsi_conn {struct iscsi_session* session; } ;
typedef  int /*<<< orphan*/  itt_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* parse_pdu_itt ) (struct iscsi_conn*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RESERVED_ITT ; 
 int get_itt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct iscsi_conn*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

struct iscsi_task *iscsi_itt_to_task(struct iscsi_conn *conn, itt_t itt)
{
	struct iscsi_session *session = conn->session;
	int i;

	if (itt == RESERVED_ITT)
		return NULL;

	if (session->tt->parse_pdu_itt)
		session->tt->parse_pdu_itt(conn, itt, &i, NULL);
	else
		i = get_itt(itt);
	if (i >= session->cmds_max)
		return NULL;

	return session->cmds[i];
}