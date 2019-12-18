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
struct xfs_btree_block {int /*<<< orphan*/  bb_numrecs; } ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int xfs_btree_get_numrecs(struct xfs_btree_block *block)
{
	return be16_to_cpu(block->bb_numrecs);
}