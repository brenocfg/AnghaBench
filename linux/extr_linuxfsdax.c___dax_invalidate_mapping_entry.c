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
struct radix_tree_root {int dummy; } ;
struct address_space {int /*<<< orphan*/  nrexceptional; struct radix_tree_root i_pages; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PAGECACHE_TAG_TOWRITE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dax_disassociate_entry (void*,struct address_space*,int) ; 
 void* get_unlocked_mapping_entry (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unlocked_mapping_entry (struct address_space*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  radix_tree_delete (struct radix_tree_root*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_exceptional_entry (void*) ; 
 scalar_t__ radix_tree_tag_get (struct radix_tree_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_lock_irq (struct radix_tree_root*) ; 
 int /*<<< orphan*/  xa_unlock_irq (struct radix_tree_root*) ; 

__attribute__((used)) static int __dax_invalidate_mapping_entry(struct address_space *mapping,
					  pgoff_t index, bool trunc)
{
	int ret = 0;
	void *entry;
	struct radix_tree_root *pages = &mapping->i_pages;

	xa_lock_irq(pages);
	entry = get_unlocked_mapping_entry(mapping, index, NULL);
	if (!entry || WARN_ON_ONCE(!radix_tree_exceptional_entry(entry)))
		goto out;
	if (!trunc &&
	    (radix_tree_tag_get(pages, index, PAGECACHE_TAG_DIRTY) ||
	     radix_tree_tag_get(pages, index, PAGECACHE_TAG_TOWRITE)))
		goto out;
	dax_disassociate_entry(entry, mapping, trunc);
	radix_tree_delete(pages, index);
	mapping->nrexceptional--;
	ret = 1;
out:
	put_unlocked_mapping_entry(mapping, index, entry);
	xa_unlock_irq(pages);
	return ret;
}