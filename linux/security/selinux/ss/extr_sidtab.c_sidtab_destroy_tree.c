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
union sidtab_entry_inner {int /*<<< orphan*/  context; struct sidtab_node_leaf* ptr_leaf; struct sidtab_node_leaf* ptr_inner; } ;
typedef  scalar_t__ u32 ;
struct sidtab_node_leaf {union sidtab_entry_inner* entries; } ;
struct sidtab_node_inner {union sidtab_entry_inner* entries; } ;

/* Variables and functions */
 scalar_t__ SIDTAB_INNER_ENTRIES ; 
 scalar_t__ SIDTAB_LEAF_ENTRIES ; 
 int /*<<< orphan*/  context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct sidtab_node_leaf*) ; 

__attribute__((used)) static void sidtab_destroy_tree(union sidtab_entry_inner entry, u32 level)
{
	u32 i;

	if (level != 0) {
		struct sidtab_node_inner *node = entry.ptr_inner;

		if (!node)
			return;

		for (i = 0; i < SIDTAB_INNER_ENTRIES; i++)
			sidtab_destroy_tree(node->entries[i], level - 1);
		kfree(node);
	} else {
		struct sidtab_node_leaf *node = entry.ptr_leaf;

		if (!node)
			return;

		for (i = 0; i < SIDTAB_LEAF_ENTRIES; i++)
			context_destroy(&node->entries[i].context);
		kfree(node);
	}
}