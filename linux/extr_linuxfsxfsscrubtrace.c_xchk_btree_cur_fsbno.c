#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
struct TYPE_8__ {int /*<<< orphan*/  agno; } ;
struct TYPE_7__ {TYPE_1__* ip; } ;
struct TYPE_9__ {TYPE_3__ a; TYPE_2__ b; } ;
struct xfs_btree_cur {int bc_nlevels; int bc_flags; TYPE_4__ bc_private; int /*<<< orphan*/  bc_mp; TYPE_5__** bc_bufs; } ;
struct TYPE_10__ {int /*<<< orphan*/  b_bn; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULLFSBLOCK ; 
 int /*<<< orphan*/  XFS_AGB_TO_FSB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XFS_BTREE_LONG_PTRS ; 
 int /*<<< orphan*/  XFS_DADDR_TO_FSB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_INO_TO_FSB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline xfs_fsblock_t
xchk_btree_cur_fsbno(
	struct xfs_btree_cur	*cur,
	int			level)
{
	if (level < cur->bc_nlevels && cur->bc_bufs[level])
		return XFS_DADDR_TO_FSB(cur->bc_mp, cur->bc_bufs[level]->b_bn);
	else if (level == cur->bc_nlevels - 1 &&
		 cur->bc_flags & XFS_BTREE_LONG_PTRS)
		return XFS_INO_TO_FSB(cur->bc_mp, cur->bc_private.b.ip->i_ino);
	else if (!(cur->bc_flags & XFS_BTREE_LONG_PTRS))
		return XFS_AGB_TO_FSB(cur->bc_mp, cur->bc_private.a.agno, 0);
	return NULLFSBLOCK;
}