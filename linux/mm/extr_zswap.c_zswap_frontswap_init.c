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
struct zswap_tree {int /*<<< orphan*/  lock; int /*<<< orphan*/  rbroot; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RB_ROOT ; 
 struct zswap_tree* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct zswap_tree** zswap_trees ; 

__attribute__((used)) static void zswap_frontswap_init(unsigned type)
{
	struct zswap_tree *tree;

	tree = kzalloc(sizeof(*tree), GFP_KERNEL);
	if (!tree) {
		pr_err("alloc failed, zswap disabled for swap type %d\n", type);
		return;
	}

	tree->rbroot = RB_ROOT;
	spin_lock_init(&tree->lock);
	zswap_trees[type] = tree;
}