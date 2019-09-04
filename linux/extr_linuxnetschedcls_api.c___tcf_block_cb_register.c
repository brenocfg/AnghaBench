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
typedef  int /*<<< orphan*/  tc_setup_cb_t ;
struct tcf_block_cb {int /*<<< orphan*/  list; void* cb_priv; void* cb_ident; int /*<<< orphan*/ * cb; } ;
struct tcf_block {int /*<<< orphan*/  cb_list; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct tcf_block_cb* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tcf_block_cb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_block_offload_in_use (struct tcf_block*) ; 
 int tcf_block_playback_offloads (struct tcf_block*,int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

struct tcf_block_cb *__tcf_block_cb_register(struct tcf_block *block,
					     tc_setup_cb_t *cb, void *cb_ident,
					     void *cb_priv,
					     struct netlink_ext_ack *extack)
{
	struct tcf_block_cb *block_cb;
	int err;

	/* Replay any already present rules */
	err = tcf_block_playback_offloads(block, cb, cb_priv, true,
					  tcf_block_offload_in_use(block),
					  extack);
	if (err)
		return ERR_PTR(err);

	block_cb = kzalloc(sizeof(*block_cb), GFP_KERNEL);
	if (!block_cb)
		return ERR_PTR(-ENOMEM);
	block_cb->cb = cb;
	block_cb->cb_ident = cb_ident;
	block_cb->cb_priv = cb_priv;
	list_add(&block_cb->list, &block->cb_list);
	return block_cb;
}