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
typedef  scalar_t__ u32 ;
struct tipc_msg {int dummy; } ;
struct tipc_member {int /*<<< orphan*/  bc_rcv_nxt; int /*<<< orphan*/  list; int /*<<< orphan*/  state; int /*<<< orphan*/  bc_syncpt; scalar_t__ instance; } ;
struct tipc_group {scalar_t__ portid; int /*<<< orphan*/  loopback; struct net* net; } ;
struct TYPE_2__ {scalar_t__ node; scalar_t__ ref; } ;
struct tipc_event {scalar_t__ found_lower; int event; TYPE_1__ port; } ;
struct sk_buff_head {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRP_JOIN_MSG ; 
 int /*<<< orphan*/  MBR_JOINED ; 
 int /*<<< orphan*/  MBR_JOINING ; 
 int /*<<< orphan*/  MBR_LEAVING ; 
 int /*<<< orphan*/  MBR_PUBLISHED ; 
#define  TIPC_PUBLISHED 129 
#define  TIPC_WITHDRAWN 128 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ msg_data (struct tipc_msg*) ; 
 int /*<<< orphan*/  tipc_group_create_event (struct tipc_group*,struct tipc_member*,int const,int /*<<< orphan*/ ,struct sk_buff_head*) ; 
 struct tipc_member* tipc_group_create_member (struct tipc_group*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_group_decr_active (struct tipc_group*,struct tipc_member*) ; 
 struct tipc_member* tipc_group_find_member (struct tipc_group*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tipc_group_open (struct tipc_member*,int*) ; 
 int /*<<< orphan*/  tipc_group_proto_xmit (struct tipc_group*,struct tipc_member*,int /*<<< orphan*/ ,struct sk_buff_head*) ; 
 int tipc_group_rcvbuf_limit (struct tipc_group*) ; 
 int /*<<< orphan*/  tipc_group_update_member (struct tipc_member*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_is_up (struct net*,scalar_t__) ; 
 scalar_t__ tipc_own_addr (struct net*) ; 

void tipc_group_member_evt(struct tipc_group *grp,
			   bool *usr_wakeup,
			   int *sk_rcvbuf,
			   struct tipc_msg *hdr,
			   struct sk_buff_head *inputq,
			   struct sk_buff_head *xmitq)
{
	struct tipc_event *evt = (void *)msg_data(hdr);
	u32 instance = evt->found_lower;
	u32 node = evt->port.node;
	u32 port = evt->port.ref;
	int event = evt->event;
	struct tipc_member *m;
	struct net *net;
	u32 self;

	if (!grp)
		return;

	net = grp->net;
	self = tipc_own_addr(net);
	if (!grp->loopback && node == self && port == grp->portid)
		return;

	m = tipc_group_find_member(grp, node, port);

	switch (event) {
	case TIPC_PUBLISHED:
		/* Send and wait for arrival of JOIN message if necessary */
		if (!m) {
			m = tipc_group_create_member(grp, node, port, instance,
						     MBR_PUBLISHED);
			if (!m)
				break;
			tipc_group_update_member(m, 0);
			tipc_group_proto_xmit(grp, m, GRP_JOIN_MSG, xmitq);
			break;
		}

		if (m->state != MBR_JOINING)
			break;

		/* Member can be taken into service */
		m->instance = instance;
		m->state = MBR_JOINED;
		tipc_group_open(m, usr_wakeup);
		tipc_group_update_member(m, 0);
		tipc_group_proto_xmit(grp, m, GRP_JOIN_MSG, xmitq);
		tipc_group_create_event(grp, m, TIPC_PUBLISHED,
					m->bc_syncpt, inputq);
		break;
	case TIPC_WITHDRAWN:
		if (!m)
			break;

		tipc_group_decr_active(grp, m);
		m->state = MBR_LEAVING;
		list_del_init(&m->list);
		tipc_group_open(m, usr_wakeup);

		/* Only send event if no LEAVE message can be expected */
		if (!tipc_node_is_up(net, node))
			tipc_group_create_event(grp, m, TIPC_WITHDRAWN,
						m->bc_rcv_nxt, inputq);
		break;
	default:
		break;
	}
	*sk_rcvbuf = tipc_group_rcvbuf_limit(grp);
}