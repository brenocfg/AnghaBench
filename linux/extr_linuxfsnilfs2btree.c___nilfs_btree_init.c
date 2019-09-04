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
struct nilfs_bmap {int /*<<< orphan*/  b_nchildren_per_block; int /*<<< orphan*/ * b_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_BTREE_NODE_NCHILDREN_MAX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_btree_node_size (struct nilfs_bmap*) ; 
 int /*<<< orphan*/  nilfs_btree_ops ; 

__attribute__((used)) static void __nilfs_btree_init(struct nilfs_bmap *bmap)
{
	bmap->b_ops = &nilfs_btree_ops;
	bmap->b_nchildren_per_block =
		NILFS_BTREE_NODE_NCHILDREN_MAX(nilfs_btree_node_size(bmap));
}