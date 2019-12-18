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
struct nilfs_bmap {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; } ;

/* Variables and functions */
 int /*<<< orphan*/  nilfs_bmap_get_dat (struct nilfs_bmap*) ; 
 int nilfs_dat_mark_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_btree_propagate_gc(struct nilfs_bmap *btree,
				    struct buffer_head *bh)
{
	return nilfs_dat_mark_dirty(nilfs_bmap_get_dat(btree), bh->b_blocknr);
}