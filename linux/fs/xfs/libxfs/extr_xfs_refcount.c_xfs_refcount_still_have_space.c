#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned long shape_changes; int nr_ops; } ;
struct TYPE_12__ {TYPE_3__ refc; } ;
struct TYPE_13__ {TYPE_4__ priv; } ;
struct TYPE_14__ {TYPE_5__ a; } ;
struct xfs_btree_cur {TYPE_6__ bc_private; TYPE_2__* bc_tp; TYPE_7__* bc_mp; } ;
struct TYPE_9__ {unsigned long sb_blocksize; } ;
struct TYPE_15__ {TYPE_1__ m_sb; } ;
struct TYPE_10__ {unsigned long t_log_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_ERRTAG_REFCOUNT_CONTINUE_UPDATE ; 
 unsigned long XFS_REFCOUNT_ITEM_OVERHEAD ; 
 scalar_t__ XFS_TEST_ERROR (int,TYPE_7__*,int /*<<< orphan*/ ) ; 
 unsigned long xfs_allocfree_log_count (TYPE_7__*,int) ; 

__attribute__((used)) static bool
xfs_refcount_still_have_space(
	struct xfs_btree_cur		*cur)
{
	unsigned long			overhead;

	overhead = cur->bc_private.a.priv.refc.shape_changes *
			xfs_allocfree_log_count(cur->bc_mp, 1);
	overhead *= cur->bc_mp->m_sb.sb_blocksize;

	/*
	 * Only allow 2 refcount extent updates per transaction if the
	 * refcount continue update "error" has been injected.
	 */
	if (cur->bc_private.a.priv.refc.nr_ops > 2 &&
	    XFS_TEST_ERROR(false, cur->bc_mp,
			XFS_ERRTAG_REFCOUNT_CONTINUE_UPDATE))
		return false;

	if (cur->bc_private.a.priv.refc.nr_ops == 0)
		return true;
	else if (overhead > cur->bc_tp->t_log_res)
		return false;
	return  cur->bc_tp->t_log_res - overhead >
		cur->bc_private.a.priv.refc.nr_ops * XFS_REFCOUNT_ITEM_OVERHEAD;
}