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

/* Variables and functions */
 int /*<<< orphan*/  __tcf_block_cb_unregister (struct tcf_block*,struct tcf_block_cb*) ; 
 struct tcf_block_cb* tcf_block_cb_lookup (struct tcf_block*,int /*<<< orphan*/ *,void*) ; 

void tcf_block_cb_unregister(struct tcf_block *block,
			     tc_setup_cb_t *cb, void *cb_ident)
{
	struct tcf_block_cb *block_cb;

	block_cb = tcf_block_cb_lookup(block, cb, cb_ident);
	if (!block_cb)
		return;
	__tcf_block_cb_unregister(block, block_cb);
}