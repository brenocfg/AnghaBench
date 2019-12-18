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
struct tcf_block_ext_info {int /*<<< orphan*/  member_0; } ;
struct tcf_block {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcf_block_put_ext (struct tcf_block*,int /*<<< orphan*/ ,struct tcf_block_ext_info*) ; 

void tcf_block_put(struct tcf_block *block)
{
	struct tcf_block_ext_info ei = {0, };

	if (!block)
		return;
	tcf_block_put_ext(block, block->q, &ei);
}