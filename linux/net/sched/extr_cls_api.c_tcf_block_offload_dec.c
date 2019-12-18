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
typedef  int u32 ;
struct tcf_block {int /*<<< orphan*/  offloadcnt; } ;

/* Variables and functions */
 int TCA_CLS_FLAGS_IN_HW ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcf_block_offload_dec(struct tcf_block *block, u32 *flags)
{
	if (!(*flags & TCA_CLS_FLAGS_IN_HW))
		return;
	*flags &= ~TCA_CLS_FLAGS_IN_HW;
	atomic_dec(&block->offloadcnt);
}