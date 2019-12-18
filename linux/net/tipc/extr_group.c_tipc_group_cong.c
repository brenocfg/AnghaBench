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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_member {int window; int advertised; int state; } ;
struct tipc_group {int* open; int /*<<< orphan*/  net; } ;
struct sk_buff_head {int dummy; } ;

/* Variables and functions */
 int ADV_ACTIVE ; 
 int ADV_IDLE ; 
 int /*<<< orphan*/  GRP_ADV_MSG ; 
 int MBR_ACTIVE ; 
 int MBR_JOINED ; 
 int MBR_PENDING ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 struct tipc_member* tipc_group_find_dest (struct tipc_group*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_group_is_receiver (struct tipc_member*) ; 
 int /*<<< orphan*/  tipc_group_proto_xmit (struct tipc_group*,struct tipc_member*,int /*<<< orphan*/ ,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_node_distr_xmit (int /*<<< orphan*/ ,struct sk_buff_head*) ; 

bool tipc_group_cong(struct tipc_group *grp, u32 dnode, u32 dport,
		     int len, struct tipc_member **mbr)
{
	struct sk_buff_head xmitq;
	struct tipc_member *m;
	int adv, state;

	m = tipc_group_find_dest(grp, dnode, dport);
	if (!tipc_group_is_receiver(m)) {
		*mbr = NULL;
		return false;
	}
	*mbr = m;

	if (m->window >= len)
		return false;

	*grp->open = false;

	/* If not fully advertised, do it now to prevent mutual blocking */
	adv = m->advertised;
	state = m->state;
	if (state == MBR_JOINED && adv == ADV_IDLE)
		return true;
	if (state == MBR_ACTIVE && adv == ADV_ACTIVE)
		return true;
	if (state == MBR_PENDING && adv == ADV_IDLE)
		return true;
	__skb_queue_head_init(&xmitq);
	tipc_group_proto_xmit(grp, m, GRP_ADV_MSG, &xmitq);
	tipc_node_distr_xmit(grp->net, &xmitq);
	return true;
}