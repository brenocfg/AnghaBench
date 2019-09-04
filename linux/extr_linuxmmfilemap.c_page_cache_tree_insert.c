#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct radix_tree_node {int dummy; } ;
struct page {int /*<<< orphan*/  index; } ;
struct TYPE_3__ {int /*<<< orphan*/  xa_lock; } ;
struct address_space {int /*<<< orphan*/  nrpages; TYPE_1__ i_pages; int /*<<< orphan*/  nrexceptional; } ;

/* Variables and functions */
 int EEXIST ; 
 int __radix_tree_create (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct radix_tree_node**,void***) ; 
 int /*<<< orphan*/  __radix_tree_replace (TYPE_1__*,struct radix_tree_node*,void**,struct page*,int /*<<< orphan*/ ) ; 
 void* radix_tree_deref_slot_protected (void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_exceptional_entry (void*) ; 
 int /*<<< orphan*/  workingset_lookup_update (struct address_space*) ; 

__attribute__((used)) static int page_cache_tree_insert(struct address_space *mapping,
				  struct page *page, void **shadowp)
{
	struct radix_tree_node *node;
	void **slot;
	int error;

	error = __radix_tree_create(&mapping->i_pages, page->index, 0,
				    &node, &slot);
	if (error)
		return error;
	if (*slot) {
		void *p;

		p = radix_tree_deref_slot_protected(slot,
						    &mapping->i_pages.xa_lock);
		if (!radix_tree_exceptional_entry(p))
			return -EEXIST;

		mapping->nrexceptional--;
		if (shadowp)
			*shadowp = p;
	}
	__radix_tree_replace(&mapping->i_pages, node, slot, page,
			     workingset_lookup_update(mapping));
	mapping->nrpages++;
	return 0;
}