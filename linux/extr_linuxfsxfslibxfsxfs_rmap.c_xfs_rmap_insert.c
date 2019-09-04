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
typedef  int /*<<< orphan*/  xfs_extlen_t ;
typedef  int /*<<< orphan*/  xfs_agblock_t ;
typedef  void* uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  agno; } ;
struct TYPE_8__ {TYPE_3__ a; } ;
struct TYPE_5__ {unsigned int rm_flags; void* rm_offset; void* rm_owner; int /*<<< orphan*/  rm_blockcount; int /*<<< orphan*/  rm_startblock; } ;
struct TYPE_6__ {TYPE_1__ r; } ;
struct xfs_btree_cur {TYPE_4__ bc_private; int /*<<< orphan*/  bc_mp; TYPE_2__ bc_rec; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_WANT_CORRUPTED_GOTO (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  trace_xfs_rmap_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,unsigned int) ; 
 int /*<<< orphan*/  trace_xfs_rmap_insert_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int xfs_btree_insert (struct xfs_btree_cur*,int*) ; 
 int xfs_rmap_lookup_eq (struct xfs_btree_cur*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,unsigned int,int*) ; 

int
xfs_rmap_insert(
	struct xfs_btree_cur	*rcur,
	xfs_agblock_t		agbno,
	xfs_extlen_t		len,
	uint64_t		owner,
	uint64_t		offset,
	unsigned int		flags)
{
	int			i;
	int			error;

	trace_xfs_rmap_insert(rcur->bc_mp, rcur->bc_private.a.agno, agbno,
			len, owner, offset, flags);

	error = xfs_rmap_lookup_eq(rcur, agbno, len, owner, offset, flags, &i);
	if (error)
		goto done;
	XFS_WANT_CORRUPTED_GOTO(rcur->bc_mp, i == 0, done);

	rcur->bc_rec.r.rm_startblock = agbno;
	rcur->bc_rec.r.rm_blockcount = len;
	rcur->bc_rec.r.rm_owner = owner;
	rcur->bc_rec.r.rm_offset = offset;
	rcur->bc_rec.r.rm_flags = flags;
	error = xfs_btree_insert(rcur, &i);
	if (error)
		goto done;
	XFS_WANT_CORRUPTED_GOTO(rcur->bc_mp, i == 1, done);
done:
	if (error)
		trace_xfs_rmap_insert_error(rcur->bc_mp,
				rcur->bc_private.a.agno, error, _RET_IP_);
	return error;
}