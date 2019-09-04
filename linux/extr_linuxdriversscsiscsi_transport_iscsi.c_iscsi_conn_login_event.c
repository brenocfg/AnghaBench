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
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct TYPE_3__ {int state; int /*<<< orphan*/  sid; int /*<<< orphan*/  cid; } ;
struct TYPE_4__ {TYPE_1__ conn_login; } ;
struct iscsi_uevent {TYPE_2__ r; int /*<<< orphan*/  type; int /*<<< orphan*/  transport_handle; } ;
struct iscsi_internal {int dummy; } ;
struct iscsi_cls_conn {int /*<<< orphan*/  cid; int /*<<< orphan*/  transport; } ;
typedef  enum iscsi_conn_state { ____Placeholder_iscsi_conn_state } iscsi_conn_state ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ISCSI_KEVENT_CONN_LOGIN_STATE ; 
 int /*<<< orphan*/  ISCSI_NL_GRP_ISCSID ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 struct nlmsghdr* __nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_cls_conn_printk (int /*<<< orphan*/ ,struct iscsi_cls_conn*,char*,int) ; 
 int /*<<< orphan*/  iscsi_conn_get_sid (struct iscsi_cls_conn*) ; 
 int /*<<< orphan*/  iscsi_handle (int /*<<< orphan*/ ) ; 
 struct iscsi_internal* iscsi_if_transport_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_multicast_skb (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iscsi_uevent* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_total_size (int) ; 

void iscsi_conn_login_event(struct iscsi_cls_conn *conn,
			    enum iscsi_conn_state state)
{
	struct nlmsghdr *nlh;
	struct sk_buff  *skb;
	struct iscsi_uevent *ev;
	struct iscsi_internal *priv;
	int len = nlmsg_total_size(sizeof(*ev));

	priv = iscsi_if_transport_lookup(conn->transport);
	if (!priv)
		return;

	skb = alloc_skb(len, GFP_ATOMIC);
	if (!skb) {
		iscsi_cls_conn_printk(KERN_ERR, conn, "gracefully ignored "
				      "conn login (%d)\n", state);
		return;
	}

	nlh = __nlmsg_put(skb, 0, 0, 0, (len - sizeof(*nlh)), 0);
	ev = nlmsg_data(nlh);
	ev->transport_handle = iscsi_handle(conn->transport);
	ev->type = ISCSI_KEVENT_CONN_LOGIN_STATE;
	ev->r.conn_login.state = state;
	ev->r.conn_login.cid = conn->cid;
	ev->r.conn_login.sid = iscsi_conn_get_sid(conn);
	iscsi_multicast_skb(skb, ISCSI_NL_GRP_ISCSID, GFP_ATOMIC);

	iscsi_cls_conn_printk(KERN_INFO, conn, "detected conn login (%d)\n",
			      state);
}