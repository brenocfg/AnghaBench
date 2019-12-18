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
struct xfs_dir2_leaf_entry {int dummy; } ;
struct xfs_dir2_block_tail {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct xfs_dir2_leaf_entry *
xfs_dir2_block_leaf_p(struct xfs_dir2_block_tail *btp)
{
	return ((struct xfs_dir2_leaf_entry *)btp) - be32_to_cpu(btp->count);
}