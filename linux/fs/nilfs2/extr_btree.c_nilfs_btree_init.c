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
struct nilfs_bmap {int /*<<< orphan*/  b_inode; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  __nilfs_btree_init (struct nilfs_bmap*) ; 
 int /*<<< orphan*/  nilfs_btree_get_root (struct nilfs_bmap*) ; 
 scalar_t__ nilfs_btree_root_broken (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nilfs_btree_init(struct nilfs_bmap *bmap)
{
	int ret = 0;

	__nilfs_btree_init(bmap);

	if (nilfs_btree_root_broken(nilfs_btree_get_root(bmap), bmap->b_inode))
		ret = -EIO;
	return ret;
}