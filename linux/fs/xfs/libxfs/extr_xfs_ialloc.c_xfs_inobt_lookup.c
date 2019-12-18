#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_lookup_t ;
typedef  int /*<<< orphan*/  xfs_agino_t ;
struct TYPE_4__ {scalar_t__ ir_free; scalar_t__ ir_freecount; scalar_t__ ir_count; scalar_t__ ir_holemask; int /*<<< orphan*/  ir_startino; } ;
struct TYPE_3__ {TYPE_2__ i; } ;
struct xfs_btree_cur {TYPE_1__ bc_rec; } ;

/* Variables and functions */
 int xfs_btree_lookup (struct xfs_btree_cur*,int /*<<< orphan*/ ,int*) ; 

int					/* error */
xfs_inobt_lookup(
	struct xfs_btree_cur	*cur,	/* btree cursor */
	xfs_agino_t		ino,	/* starting inode of chunk */
	xfs_lookup_t		dir,	/* <=, >=, == */
	int			*stat)	/* success/failure */
{
	cur->bc_rec.i.ir_startino = ino;
	cur->bc_rec.i.ir_holemask = 0;
	cur->bc_rec.i.ir_count = 0;
	cur->bc_rec.i.ir_freecount = 0;
	cur->bc_rec.i.ir_free = 0;
	return xfs_btree_lookup(cur, dir, stat);
}