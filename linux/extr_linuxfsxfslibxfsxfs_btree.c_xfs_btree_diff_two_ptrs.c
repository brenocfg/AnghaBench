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
union xfs_btree_ptr {int /*<<< orphan*/  s; int /*<<< orphan*/  l; } ;
struct xfs_btree_cur {int bc_flags; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int XFS_BTREE_LONG_PTRS ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 

int64_t
xfs_btree_diff_two_ptrs(
	struct xfs_btree_cur		*cur,
	const union xfs_btree_ptr	*a,
	const union xfs_btree_ptr	*b)
{
	if (cur->bc_flags & XFS_BTREE_LONG_PTRS)
		return (int64_t)be64_to_cpu(a->l) - be64_to_cpu(b->l);
	return (int64_t)be32_to_cpu(a->s) - be32_to_cpu(b->s);
}