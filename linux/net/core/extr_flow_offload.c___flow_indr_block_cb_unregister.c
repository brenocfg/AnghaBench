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
struct net_device {int dummy; } ;
struct flow_indr_block_dev {int dummy; } ;
struct flow_indr_block_cb {int /*<<< orphan*/  cb_priv; int /*<<< orphan*/  cb; } ;
typedef  int /*<<< orphan*/  flow_indr_block_bind_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_BLOCK_UNBIND ; 
 int /*<<< orphan*/  flow_block_ing_cmd (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_indr_block_cb_del (struct flow_indr_block_cb*) ; 
 struct flow_indr_block_cb* flow_indr_block_cb_lookup (struct flow_indr_block_dev*,int /*<<< orphan*/ *,void*) ; 
 struct flow_indr_block_dev* flow_indr_block_dev_lookup (struct net_device*) ; 
 int /*<<< orphan*/  flow_indr_block_dev_put (struct flow_indr_block_dev*) ; 

void __flow_indr_block_cb_unregister(struct net_device *dev,
				     flow_indr_block_bind_cb_t *cb,
				     void *cb_ident)
{
	struct flow_indr_block_cb *indr_block_cb;
	struct flow_indr_block_dev *indr_dev;

	indr_dev = flow_indr_block_dev_lookup(dev);
	if (!indr_dev)
		return;

	indr_block_cb = flow_indr_block_cb_lookup(indr_dev, cb, cb_ident);
	if (!indr_block_cb)
		return;

	flow_block_ing_cmd(dev, indr_block_cb->cb, indr_block_cb->cb_priv,
			   FLOW_BLOCK_UNBIND);

	flow_indr_block_cb_del(indr_block_cb);
	flow_indr_block_dev_put(indr_dev);
}