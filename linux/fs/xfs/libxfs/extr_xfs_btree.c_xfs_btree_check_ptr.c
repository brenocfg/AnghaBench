#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union xfs_btree_ptr {int /*<<< orphan*/  s; int /*<<< orphan*/  l; } ;
struct TYPE_7__ {int /*<<< orphan*/  agno; } ;
struct TYPE_6__ {int /*<<< orphan*/  whichfork; TYPE_1__* ip; } ;
struct TYPE_8__ {TYPE_3__ a; TYPE_2__ b; } ;
struct xfs_btree_cur {int bc_flags; int /*<<< orphan*/  bc_btnum; TYPE_4__ bc_private; int /*<<< orphan*/  bc_mp; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int XFS_BTREE_LONG_PTRS ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_btree_check_lptr (struct xfs_btree_cur*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xfs_btree_check_sptr (struct xfs_btree_cur*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,...) ; 

__attribute__((used)) static int
xfs_btree_check_ptr(
	struct xfs_btree_cur	*cur,
	union xfs_btree_ptr	*ptr,
	int			index,
	int			level)
{
	if (cur->bc_flags & XFS_BTREE_LONG_PTRS) {
		if (xfs_btree_check_lptr(cur, be64_to_cpu((&ptr->l)[index]),
				level))
			return 0;
		xfs_err(cur->bc_mp,
"Inode %llu fork %d: Corrupt btree %d pointer at level %d index %d.",
				cur->bc_private.b.ip->i_ino,
				cur->bc_private.b.whichfork, cur->bc_btnum,
				level, index);
	} else {
		if (xfs_btree_check_sptr(cur, be32_to_cpu((&ptr->s)[index]),
				level))
			return 0;
		xfs_err(cur->bc_mp,
"AG %u: Corrupt btree %d pointer at level %d index %d.",
				cur->bc_private.a.agno, cur->bc_btnum,
				level, index);
	}

	return -EFSCORRUPTED;
}