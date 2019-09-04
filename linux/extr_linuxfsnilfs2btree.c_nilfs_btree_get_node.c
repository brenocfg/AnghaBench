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
struct nilfs_btree_path {int dummy; } ;
struct nilfs_btree_node {int dummy; } ;
struct nilfs_bmap {int dummy; } ;

/* Variables and functions */
 int NILFS_BTREE_ROOT_NCHILDREN_MAX ; 
 struct nilfs_btree_node* nilfs_btree_get_nonroot_node (struct nilfs_btree_path const*,int) ; 
 struct nilfs_btree_node* nilfs_btree_get_root (struct nilfs_bmap const*) ; 
 int nilfs_btree_height (struct nilfs_bmap const*) ; 
 int nilfs_btree_nchildren_per_block (struct nilfs_bmap const*) ; 

__attribute__((used)) static struct nilfs_btree_node *
nilfs_btree_get_node(const struct nilfs_bmap *btree,
		     const struct nilfs_btree_path *path,
		     int level, int *ncmaxp)
{
	struct nilfs_btree_node *node;

	if (level == nilfs_btree_height(btree) - 1) {
		node = nilfs_btree_get_root(btree);
		*ncmaxp = NILFS_BTREE_ROOT_NCHILDREN_MAX;
	} else {
		node = nilfs_btree_get_nonroot_node(path, level);
		*ncmaxp = nilfs_btree_nchildren_per_block(btree);
	}
	return node;
}