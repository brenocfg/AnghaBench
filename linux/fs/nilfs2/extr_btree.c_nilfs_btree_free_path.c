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
struct nilfs_btree_path {int /*<<< orphan*/  bp_bh; } ;

/* Variables and functions */
 int NILFS_BTREE_LEVEL_DATA ; 
 int NILFS_BTREE_LEVEL_MAX ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nilfs_btree_path*) ; 
 int /*<<< orphan*/  nilfs_btree_path_cache ; 

__attribute__((used)) static void nilfs_btree_free_path(struct nilfs_btree_path *path)
{
	int level = NILFS_BTREE_LEVEL_DATA;

	for (; level < NILFS_BTREE_LEVEL_MAX; level++)
		brelse(path[level].bp_bh);

	kmem_cache_free(nilfs_btree_path_cache, path);
}