#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nilfs_bmap {int /*<<< orphan*/  b_sem; TYPE_1__* b_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* bop_clear ) (struct nilfs_bmap*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nilfs_bmap*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void nilfs_bmap_clear(struct nilfs_bmap *bmap)
{
	down_write(&bmap->b_sem);
	if (bmap->b_ops->bop_clear != NULL)
		bmap->b_ops->bop_clear(bmap);
	up_write(&bmap->b_sem);
}