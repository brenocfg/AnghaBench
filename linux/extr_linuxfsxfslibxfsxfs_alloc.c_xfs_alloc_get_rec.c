#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_extlen_t ;
typedef  scalar_t__ xfs_agnumber_t ;
typedef  char* xfs_agblock_t ;
struct TYPE_6__ {int /*<<< orphan*/  ar_blockcount; int /*<<< orphan*/  ar_startblock; } ;
union xfs_btree_rec {TYPE_3__ alloc; } ;
struct xfs_mount {int dummy; } ;
struct TYPE_4__ {scalar_t__ agno; } ;
struct TYPE_5__ {TYPE_1__ a; } ;
struct xfs_btree_cur {scalar_t__ bc_btnum; TYPE_2__ bc_private; struct xfs_mount* bc_mp; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 scalar_t__ XFS_BTNUM_BNO ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int xfs_btree_get_rec (struct xfs_btree_cur*,union xfs_btree_rec**,int*) ; 
 int /*<<< orphan*/  xfs_verify_agbno (struct xfs_mount*,scalar_t__,char*) ; 
 int /*<<< orphan*/  xfs_warn (struct xfs_mount*,char*,char*,scalar_t__) ; 

int					/* error */
xfs_alloc_get_rec(
	struct xfs_btree_cur	*cur,	/* btree cursor */
	xfs_agblock_t		*bno,	/* output: starting block of extent */
	xfs_extlen_t		*len,	/* output: length of extent */
	int			*stat)	/* output: success/failure */
{
	struct xfs_mount	*mp = cur->bc_mp;
	xfs_agnumber_t		agno = cur->bc_private.a.agno;
	union xfs_btree_rec	*rec;
	int			error;

	error = xfs_btree_get_rec(cur, &rec, stat);
	if (error || !(*stat))
		return error;

	*bno = be32_to_cpu(rec->alloc.ar_startblock);
	*len = be32_to_cpu(rec->alloc.ar_blockcount);

	if (*len == 0)
		goto out_bad_rec;

	/* check for valid extent range, including overflow */
	if (!xfs_verify_agbno(mp, agno, *bno))
		goto out_bad_rec;
	if (*bno > *bno + *len)
		goto out_bad_rec;
	if (!xfs_verify_agbno(mp, agno, *bno + *len - 1))
		goto out_bad_rec;

	return 0;

out_bad_rec:
	xfs_warn(mp,
		"%s Freespace BTree record corruption in AG %d detected!",
		cur->bc_btnum == XFS_BTNUM_BNO ? "Block" : "Size", agno);
	xfs_warn(mp,
		"start block 0x%x block count 0x%x", *bno, *len);
	return -EFSCORRUPTED;
}