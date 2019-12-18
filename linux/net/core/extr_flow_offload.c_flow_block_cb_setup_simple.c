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
struct list_head {int dummy; } ;
struct flow_block_offload {scalar_t__ binder_type; int command; int /*<<< orphan*/  block; struct list_head* driver_block_list; } ;
struct flow_block_cb {int /*<<< orphan*/  driver_list; } ;
typedef  int /*<<< orphan*/  flow_setup_cb_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
#define  FLOW_BLOCK_BIND 129 
 scalar_t__ FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS ; 
#define  FLOW_BLOCK_UNBIND 128 
 int /*<<< orphan*/  IS_ERR (struct flow_block_cb*) ; 
 int PTR_ERR (struct flow_block_cb*) ; 
 int /*<<< orphan*/  flow_block_cb_add (struct flow_block_cb*,struct flow_block_offload*) ; 
 struct flow_block_cb* flow_block_cb_alloc (int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flow_block_cb_is_busy (int /*<<< orphan*/ *,void*,struct list_head*) ; 
 struct flow_block_cb* flow_block_cb_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  flow_block_cb_remove (struct flow_block_cb*,struct flow_block_offload*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

int flow_block_cb_setup_simple(struct flow_block_offload *f,
			       struct list_head *driver_block_list,
			       flow_setup_cb_t *cb,
			       void *cb_ident, void *cb_priv,
			       bool ingress_only)
{
	struct flow_block_cb *block_cb;

	if (ingress_only &&
	    f->binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS)
		return -EOPNOTSUPP;

	f->driver_block_list = driver_block_list;

	switch (f->command) {
	case FLOW_BLOCK_BIND:
		if (flow_block_cb_is_busy(cb, cb_ident, driver_block_list))
			return -EBUSY;

		block_cb = flow_block_cb_alloc(cb, cb_ident, cb_priv, NULL);
		if (IS_ERR(block_cb))
			return PTR_ERR(block_cb);

		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list, driver_block_list);
		return 0;
	case FLOW_BLOCK_UNBIND:
		block_cb = flow_block_cb_lookup(f->block, cb, cb_ident);
		if (!block_cb)
			return -ENOENT;

		flow_block_cb_remove(block_cb, f);
		list_del(&block_cb->driver_list);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}