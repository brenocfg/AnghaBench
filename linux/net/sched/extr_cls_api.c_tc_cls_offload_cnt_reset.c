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
typedef  scalar_t__ u32 ;
struct tcf_proto {int /*<<< orphan*/  lock; } ;
struct tcf_block {int /*<<< orphan*/  cb_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_block_offload_dec (struct tcf_block*,scalar_t__*) ; 

__attribute__((used)) static void
tc_cls_offload_cnt_reset(struct tcf_block *block, struct tcf_proto *tp,
			 u32 *cnt, u32 *flags)
{
	lockdep_assert_held(&block->cb_lock);

	spin_lock(&tp->lock);
	tcf_block_offload_dec(block, flags);
	*cnt = 0;
	spin_unlock(&tp->lock);
}