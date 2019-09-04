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
struct tcf_block_cb {int dummy; } ;
struct tcf_block {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (struct tcf_block_cb*) ; 
 struct tcf_block_cb* __tcf_block_cb_register (struct tcf_block*,int /*<<< orphan*/ *,void*,void*,struct netlink_ext_ack*) ; 

int tcf_block_cb_register(struct tcf_block *block,
			  tc_setup_cb_t *cb, void *cb_ident,
			  void *cb_priv, struct netlink_ext_ack *extack)
{
	struct tcf_block_cb *block_cb;

	block_cb = __tcf_block_cb_register(block, cb, cb_ident, cb_priv,
					   extack);
	return PTR_ERR_OR_ZERO(block_cb);
}