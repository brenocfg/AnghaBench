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
struct tcf_block_ext_info {int /*<<< orphan*/  binder_type; int /*<<< orphan*/  block_index; } ;
struct tcf_block {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tcf_block*) ; 
 int PTR_ERR (struct tcf_block*) ; 
 struct net* qdisc_net (struct Qdisc*) ; 
 struct tcf_block* tcf_block_create (struct net*,struct Qdisc*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int tcf_block_insert (struct tcf_block*,struct net*,struct netlink_ext_ack*) ; 
 int tcf_block_offload_bind (struct tcf_block*,struct Qdisc*,struct tcf_block_ext_info*,struct netlink_ext_ack*) ; 
 int tcf_block_owner_add (struct tcf_block*,struct Qdisc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_block_owner_del (struct tcf_block*,struct Qdisc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_block_owner_netif_keep_dst (struct tcf_block*,struct Qdisc*,int /*<<< orphan*/ ) ; 
 struct tcf_block* tcf_block_refcnt_get (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_block_refcnt_put (struct tcf_block*,int) ; 
 scalar_t__ tcf_block_shared (struct tcf_block*) ; 
 int tcf_chain0_head_change_cb_add (struct tcf_block*,struct tcf_block_ext_info*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  tcf_chain0_head_change_cb_del (struct tcf_block*,struct tcf_block_ext_info*) ; 

int tcf_block_get_ext(struct tcf_block **p_block, struct Qdisc *q,
		      struct tcf_block_ext_info *ei,
		      struct netlink_ext_ack *extack)
{
	struct net *net = qdisc_net(q);
	struct tcf_block *block = NULL;
	int err;

	if (ei->block_index)
		/* block_index not 0 means the shared block is requested */
		block = tcf_block_refcnt_get(net, ei->block_index);

	if (!block) {
		block = tcf_block_create(net, q, ei->block_index, extack);
		if (IS_ERR(block))
			return PTR_ERR(block);
		if (tcf_block_shared(block)) {
			err = tcf_block_insert(block, net, extack);
			if (err)
				goto err_block_insert;
		}
	}

	err = tcf_block_owner_add(block, q, ei->binder_type);
	if (err)
		goto err_block_owner_add;

	tcf_block_owner_netif_keep_dst(block, q, ei->binder_type);

	err = tcf_chain0_head_change_cb_add(block, ei, extack);
	if (err)
		goto err_chain0_head_change_cb_add;

	err = tcf_block_offload_bind(block, q, ei, extack);
	if (err)
		goto err_block_offload_bind;

	*p_block = block;
	return 0;

err_block_offload_bind:
	tcf_chain0_head_change_cb_del(block, ei);
err_chain0_head_change_cb_add:
	tcf_block_owner_del(block, q, ei->binder_type);
err_block_owner_add:
err_block_insert:
	tcf_block_refcnt_put(block, true);
	return err;
}