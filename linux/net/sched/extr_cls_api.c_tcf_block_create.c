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
struct TYPE_2__ {int /*<<< orphan*/  filter_chain_list; } ;
struct tcf_block {struct Qdisc* q; int /*<<< orphan*/  index; struct net* net; int /*<<< orphan*/  refcnt; TYPE_1__ chain0; int /*<<< orphan*/  owner_list; int /*<<< orphan*/  chain_list; int /*<<< orphan*/  flow_block; int /*<<< orphan*/  cb_lock; int /*<<< orphan*/  proto_destroy_lock; int /*<<< orphan*/  lock; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct tcf_block* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  flow_block_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 struct tcf_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tcf_block_shared (struct tcf_block*) ; 

__attribute__((used)) static struct tcf_block *tcf_block_create(struct net *net, struct Qdisc *q,
					  u32 block_index,
					  struct netlink_ext_ack *extack)
{
	struct tcf_block *block;

	block = kzalloc(sizeof(*block), GFP_KERNEL);
	if (!block) {
		NL_SET_ERR_MSG(extack, "Memory allocation for block failed");
		return ERR_PTR(-ENOMEM);
	}
	mutex_init(&block->lock);
	mutex_init(&block->proto_destroy_lock);
	init_rwsem(&block->cb_lock);
	flow_block_init(&block->flow_block);
	INIT_LIST_HEAD(&block->chain_list);
	INIT_LIST_HEAD(&block->owner_list);
	INIT_LIST_HEAD(&block->chain0.filter_chain_list);

	refcount_set(&block->refcnt, 1);
	block->net = net;
	block->index = block_index;

	/* Don't store q pointer for blocks which are shared */
	if (!tcf_block_shared(block))
		block->q = q;
	return block;
}