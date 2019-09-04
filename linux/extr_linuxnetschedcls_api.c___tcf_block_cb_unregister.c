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
struct tcf_block_cb {int /*<<< orphan*/  list; int /*<<< orphan*/  cb_priv; int /*<<< orphan*/  cb; } ;
struct tcf_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tcf_block_cb*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_block_offload_in_use (struct tcf_block*) ; 
 int /*<<< orphan*/  tcf_block_playback_offloads (struct tcf_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __tcf_block_cb_unregister(struct tcf_block *block,
			       struct tcf_block_cb *block_cb)
{
	tcf_block_playback_offloads(block, block_cb->cb, block_cb->cb_priv,
				    false, tcf_block_offload_in_use(block),
				    NULL);
	list_del(&block_cb->list);
	kfree(block_cb);
}