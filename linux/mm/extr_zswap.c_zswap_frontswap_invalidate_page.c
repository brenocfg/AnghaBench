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
struct zswap_entry {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zswap_entry_put (struct zswap_tree*,struct zswap_entry*) ; 
 int /*<<< orphan*/  zswap_rb_erase (int /*<<< orphan*/ *,struct zswap_entry*) ; 
 struct zswap_entry* zswap_rb_search (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct zswap_tree** zswap_trees ; 

__attribute__((used)) static void zswap_frontswap_invalidate_page(unsigned type, pgoff_t offset)
{
	struct zswap_tree *tree = zswap_trees[type];
	struct zswap_entry *entry;

	/* find */
	spin_lock(&tree->lock);
	entry = zswap_rb_search(&tree->rbroot, offset);
	if (!entry) {
		/* entry was written back */
		spin_unlock(&tree->lock);
		return;
	}

	/* remove from rbtree */
	zswap_rb_erase(&tree->rbroot, entry);

	/* drop the initial reference from entry creation */
	zswap_entry_put(tree, entry);

	spin_unlock(&tree->lock);
}