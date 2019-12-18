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
typedef  int /*<<< orphan*/  xfs_inofree_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  ir_free; int /*<<< orphan*/  ir_freecount; int /*<<< orphan*/  ir_count; int /*<<< orphan*/  ir_holemask; } ;
struct TYPE_4__ {TYPE_1__ i; } ;
struct xfs_btree_cur {TYPE_2__ bc_rec; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int xfs_btree_insert (struct xfs_btree_cur*,int*) ; 

int
xfs_inobt_insert_rec(
	struct xfs_btree_cur	*cur,
	uint16_t		holemask,
	uint8_t			count,
	int32_t			freecount,
	xfs_inofree_t		free,
	int			*stat)
{
	cur->bc_rec.i.ir_holemask = holemask;
	cur->bc_rec.i.ir_count = count;
	cur->bc_rec.i.ir_freecount = freecount;
	cur->bc_rec.i.ir_free = free;
	return xfs_btree_insert(cur, stat);
}