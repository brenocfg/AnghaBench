#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cid; int /*<<< orphan*/  sid; } ;
struct TYPE_4__ {TYPE_1__ d_conn; } ;
struct iscsi_uevent {TYPE_2__ u; } ;
struct iscsi_transport {int /*<<< orphan*/  (* destroy_conn ) (struct iscsi_cls_conn*) ;} ;
struct iscsi_cls_conn {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ISCSI_DBG_TRANS_CONN (struct iscsi_cls_conn*,char*) ; 
 struct iscsi_cls_conn* iscsi_conn_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct iscsi_cls_conn*) ; 

__attribute__((used)) static int
iscsi_if_destroy_conn(struct iscsi_transport *transport, struct iscsi_uevent *ev)
{
	struct iscsi_cls_conn *conn;

	conn = iscsi_conn_lookup(ev->u.d_conn.sid, ev->u.d_conn.cid);
	if (!conn)
		return -EINVAL;

	ISCSI_DBG_TRANS_CONN(conn, "Destroying transport conn\n");
	if (transport->destroy_conn)
		transport->destroy_conn(conn);

	return 0;
}