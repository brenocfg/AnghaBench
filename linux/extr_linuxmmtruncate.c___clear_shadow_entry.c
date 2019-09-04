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
struct radix_tree_node {int dummy; } ;
struct address_space {int /*<<< orphan*/  nrexceptional; int /*<<< orphan*/  i_pages; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  __radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct radix_tree_node**,void***) ; 
 int /*<<< orphan*/  __radix_tree_replace (int /*<<< orphan*/ *,struct radix_tree_node*,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workingset_update_node ; 

__attribute__((used)) static inline void __clear_shadow_entry(struct address_space *mapping,
				pgoff_t index, void *entry)
{
	struct radix_tree_node *node;
	void **slot;

	if (!__radix_tree_lookup(&mapping->i_pages, index, &node, &slot))
		return;
	if (*slot != entry)
		return;
	__radix_tree_replace(&mapping->i_pages, node, slot, NULL,
			     workingset_update_node);
	mapping->nrexceptional--;
}