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
struct tcf_net {int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  idr; } ;
struct tcf_block {int /*<<< orphan*/  index; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int idr_alloc_u32 (int /*<<< orphan*/ *,struct tcf_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 struct tcf_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_net_id ; 

__attribute__((used)) static int tcf_block_insert(struct tcf_block *block, struct net *net,
			    struct netlink_ext_ack *extack)
{
	struct tcf_net *tn = net_generic(net, tcf_net_id);
	int err;

	idr_preload(GFP_KERNEL);
	spin_lock(&tn->idr_lock);
	err = idr_alloc_u32(&tn->idr, block, &block->index, block->index,
			    GFP_NOWAIT);
	spin_unlock(&tn->idr_lock);
	idr_preload_end();

	return err;
}