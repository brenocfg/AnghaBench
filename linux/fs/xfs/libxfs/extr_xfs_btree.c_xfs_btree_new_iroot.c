#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union xfs_btree_ptr {int dummy; } xfs_btree_ptr ;
typedef  union xfs_btree_key {int dummy; } xfs_btree_key ;
struct xfs_buf {int /*<<< orphan*/  b_bn; } ;
struct TYPE_11__ {int /*<<< orphan*/  whichfork; int /*<<< orphan*/  ip; } ;
struct TYPE_12__ {TYPE_5__ b; } ;
struct xfs_btree_cur {int bc_flags; int bc_nlevels; int* bc_ptrs; TYPE_6__ bc_private; TYPE_1__* bc_ops; } ;
struct TYPE_9__ {void* bb_blkno; } ;
struct TYPE_8__ {void* bb_blkno; } ;
struct TYPE_10__ {TYPE_3__ s; TYPE_2__ l; } ;
struct xfs_btree_block {int /*<<< orphan*/  bb_numrecs; int /*<<< orphan*/  bb_level; TYPE_4__ bb_u; } ;
struct TYPE_7__ {int (* alloc_block ) (struct xfs_btree_cur*,union xfs_btree_ptr*,union xfs_btree_ptr*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_BB_ALL_BITS ; 
 int XFS_BTREE_CRC_BLOCKS ; 
 int XFS_BTREE_LONG_PTRS ; 
 int XFS_BTREE_ROOT_IN_INODE ; 
 int /*<<< orphan*/  XFS_BTREE_STATS_INC (struct xfs_btree_cur*,int /*<<< orphan*/ ) ; 
 int XFS_ILOG_CORE ; 
 int /*<<< orphan*/  alloc ; 
 int /*<<< orphan*/  be16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct xfs_btree_block*,struct xfs_btree_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newroot ; 
 int stub1 (struct xfs_btree_cur*,union xfs_btree_ptr*,union xfs_btree_ptr*,int*) ; 
 int /*<<< orphan*/  xfs_btree_block_len (struct xfs_btree_cur*) ; 
 int /*<<< orphan*/  xfs_btree_copy_keys (struct xfs_btree_cur*,union xfs_btree_key*,union xfs_btree_key*,int) ; 
 int /*<<< orphan*/  xfs_btree_copy_ptrs (struct xfs_btree_cur*,union xfs_btree_ptr*,union xfs_btree_ptr*,int) ; 
 int xfs_btree_debug_check_ptr (struct xfs_btree_cur*,union xfs_btree_ptr*,int,int) ; 
 int xfs_btree_get_buf_block (struct xfs_btree_cur*,union xfs_btree_ptr*,struct xfs_btree_block**,struct xfs_buf**) ; 
 struct xfs_btree_block* xfs_btree_get_iroot (struct xfs_btree_cur*) ; 
 int xfs_btree_get_numrecs (struct xfs_btree_block*) ; 
 union xfs_btree_key* xfs_btree_key_addr (struct xfs_btree_cur*,int,struct xfs_btree_block*) ; 
 int /*<<< orphan*/  xfs_btree_log_block (struct xfs_btree_cur*,struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_btree_log_keys (struct xfs_btree_cur*,struct xfs_buf*,int,int) ; 
 int /*<<< orphan*/  xfs_btree_log_ptrs (struct xfs_btree_cur*,struct xfs_buf*,int,int) ; 
 union xfs_btree_ptr* xfs_btree_ptr_addr (struct xfs_btree_cur*,int,struct xfs_btree_block*) ; 
 int /*<<< orphan*/  xfs_btree_set_numrecs (struct xfs_btree_block*,int) ; 
 int /*<<< orphan*/  xfs_btree_setbuf (struct xfs_btree_cur*,int,struct xfs_buf*) ; 
 int xfs_ilog_fbroot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iroot_realloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int						/* error */
xfs_btree_new_iroot(
	struct xfs_btree_cur	*cur,		/* btree cursor */
	int			*logflags,	/* logging flags for inode */
	int			*stat)		/* return status - 0 fail */
{
	struct xfs_buf		*cbp;		/* buffer for cblock */
	struct xfs_btree_block	*block;		/* btree block */
	struct xfs_btree_block	*cblock;	/* child btree block */
	union xfs_btree_key	*ckp;		/* child key pointer */
	union xfs_btree_ptr	*cpp;		/* child ptr pointer */
	union xfs_btree_key	*kp;		/* pointer to btree key */
	union xfs_btree_ptr	*pp;		/* pointer to block addr */
	union xfs_btree_ptr	nptr;		/* new block addr */
	int			level;		/* btree level */
	int			error;		/* error return code */
	int			i;		/* loop counter */

	XFS_BTREE_STATS_INC(cur, newroot);

	ASSERT(cur->bc_flags & XFS_BTREE_ROOT_IN_INODE);

	level = cur->bc_nlevels - 1;

	block = xfs_btree_get_iroot(cur);
	pp = xfs_btree_ptr_addr(cur, 1, block);

	/* Allocate the new block. If we can't do it, we're toast. Give up. */
	error = cur->bc_ops->alloc_block(cur, pp, &nptr, stat);
	if (error)
		goto error0;
	if (*stat == 0)
		return 0;

	XFS_BTREE_STATS_INC(cur, alloc);

	/* Copy the root into a real block. */
	error = xfs_btree_get_buf_block(cur, &nptr, &cblock, &cbp);
	if (error)
		goto error0;

	/*
	 * we can't just memcpy() the root in for CRC enabled btree blocks.
	 * In that case have to also ensure the blkno remains correct
	 */
	memcpy(cblock, block, xfs_btree_block_len(cur));
	if (cur->bc_flags & XFS_BTREE_CRC_BLOCKS) {
		if (cur->bc_flags & XFS_BTREE_LONG_PTRS)
			cblock->bb_u.l.bb_blkno = cpu_to_be64(cbp->b_bn);
		else
			cblock->bb_u.s.bb_blkno = cpu_to_be64(cbp->b_bn);
	}

	be16_add_cpu(&block->bb_level, 1);
	xfs_btree_set_numrecs(block, 1);
	cur->bc_nlevels++;
	cur->bc_ptrs[level + 1] = 1;

	kp = xfs_btree_key_addr(cur, 1, block);
	ckp = xfs_btree_key_addr(cur, 1, cblock);
	xfs_btree_copy_keys(cur, ckp, kp, xfs_btree_get_numrecs(cblock));

	cpp = xfs_btree_ptr_addr(cur, 1, cblock);
	for (i = 0; i < be16_to_cpu(cblock->bb_numrecs); i++) {
		error = xfs_btree_debug_check_ptr(cur, pp, i, level);
		if (error)
			goto error0;
	}

	xfs_btree_copy_ptrs(cur, cpp, pp, xfs_btree_get_numrecs(cblock));

	error = xfs_btree_debug_check_ptr(cur, &nptr, 0, level);
	if (error)
		goto error0;

	xfs_btree_copy_ptrs(cur, pp, &nptr, 1);

	xfs_iroot_realloc(cur->bc_private.b.ip,
			  1 - xfs_btree_get_numrecs(cblock),
			  cur->bc_private.b.whichfork);

	xfs_btree_setbuf(cur, level, cbp);

	/*
	 * Do all this logging at the end so that
	 * the root is at the right level.
	 */
	xfs_btree_log_block(cur, cbp, XFS_BB_ALL_BITS);
	xfs_btree_log_keys(cur, cbp, 1, be16_to_cpu(cblock->bb_numrecs));
	xfs_btree_log_ptrs(cur, cbp, 1, be16_to_cpu(cblock->bb_numrecs));

	*logflags |=
		XFS_ILOG_CORE | xfs_ilog_fbroot(cur->bc_private.b.whichfork);
	*stat = 1;
	return 0;
error0:
	return error;
}