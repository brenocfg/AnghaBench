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
struct tcf_block {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 struct tcf_block* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct tcf_block*) ; 
 int PTR_ERR (struct tcf_block*) ; 
 struct tcf_block* __tcf_block_find (struct net*,struct Qdisc*,unsigned long,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int __tcf_qdisc_cl_find (struct Qdisc*,int /*<<< orphan*/ ,unsigned long*,int,struct netlink_ext_ack*) ; 
 int __tcf_qdisc_find (struct net*,struct Qdisc**,int /*<<< orphan*/ *,int,int,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  qdisc_put (struct Qdisc*) ; 

__attribute__((used)) static struct tcf_block *tcf_block_find(struct net *net, struct Qdisc **q,
					u32 *parent, unsigned long *cl,
					int ifindex, u32 block_index,
					struct netlink_ext_ack *extack)
{
	struct tcf_block *block;
	int err = 0;

	ASSERT_RTNL();

	err = __tcf_qdisc_find(net, q, parent, ifindex, true, extack);
	if (err)
		goto errout;

	err = __tcf_qdisc_cl_find(*q, *parent, cl, ifindex, extack);
	if (err)
		goto errout_qdisc;

	block = __tcf_block_find(net, *q, *cl, ifindex, block_index, extack);
	if (IS_ERR(block)) {
		err = PTR_ERR(block);
		goto errout_qdisc;
	}

	return block;

errout_qdisc:
	if (*q)
		qdisc_put(*q);
errout:
	*q = NULL;
	return ERR_PTR(err);
}