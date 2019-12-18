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
 int ENOMEM ; 
 int /*<<< orphan*/  FLOW_BLOCK_BIND ; 
 int PTR_ERR_OR_ZERO (struct flow_indr_block_cb*) ; 
 int /*<<< orphan*/  flow_block_ing_cmd (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct flow_indr_block_cb* flow_indr_block_cb_add (struct flow_indr_block_dev*,void*,int /*<<< orphan*/ *,void*) ; 
 struct flow_indr_block_dev* flow_indr_block_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  flow_indr_block_dev_put (struct flow_indr_block_dev*) ; 

int __flow_indr_block_cb_register(struct net_device *dev, void *cb_priv,
				  flow_indr_block_bind_cb_t *cb,
				  void *cb_ident)
{
	struct flow_indr_block_cb *indr_block_cb;
	struct flow_indr_block_dev *indr_dev;
	int err;

	indr_dev = flow_indr_block_dev_get(dev);
	if (!indr_dev)
		return -ENOMEM;

	indr_block_cb = flow_indr_block_cb_add(indr_dev, cb_priv, cb, cb_ident);
	err = PTR_ERR_OR_ZERO(indr_block_cb);
	if (err)
		goto err_dev_put;

	flow_block_ing_cmd(dev, indr_block_cb->cb, indr_block_cb->cb_priv,
			   FLOW_BLOCK_BIND);

	return 0;

err_dev_put:
	flow_indr_block_dev_put(indr_dev);
	return err;
}