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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_net {int /*<<< orphan*/  net_id; int /*<<< orphan*/  random; int /*<<< orphan*/  trial_addr; } ;
struct tipc_msg {int dummy; } ;
struct tipc_bearer {int /*<<< orphan*/  addr; TYPE_1__* media; int /*<<< orphan*/  domain; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* addr2msg ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_CONFIG ; 
 scalar_t__ MAX_H_SIZE ; 
 scalar_t__ NODE_ID_LEN ; 
 int /*<<< orphan*/  TIPC_NODE_CAPABILITIES ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_media_addr (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_bc_netid (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_dest_domain (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_node_capabilities (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_node_id (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_node_sig (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_non_seq (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_size (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_msg_init (int /*<<< orphan*/ ,struct tipc_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct tipc_net* tipc_net (struct net*) ; 
 int /*<<< orphan*/  tipc_own_id (struct net*) ; 

__attribute__((used)) static void tipc_disc_init_msg(struct net *net, struct sk_buff *skb,
			       u32 mtyp,  struct tipc_bearer *b)
{
	struct tipc_net *tn = tipc_net(net);
	u32 dest_domain = b->domain;
	struct tipc_msg *hdr;

	hdr = buf_msg(skb);
	tipc_msg_init(tn->trial_addr, hdr, LINK_CONFIG, mtyp,
		      MAX_H_SIZE, dest_domain);
	msg_set_size(hdr, MAX_H_SIZE + NODE_ID_LEN);
	msg_set_non_seq(hdr, 1);
	msg_set_node_sig(hdr, tn->random);
	msg_set_node_capabilities(hdr, TIPC_NODE_CAPABILITIES);
	msg_set_dest_domain(hdr, dest_domain);
	msg_set_bc_netid(hdr, tn->net_id);
	b->media->addr2msg(msg_media_addr(hdr), &b->addr);
	msg_set_node_id(hdr, tipc_own_id(net));
}