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
struct address_space {int /*<<< orphan*/  nrexceptional; int /*<<< orphan*/  i_pages; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PAGECACHE_TAG_TOWRITE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  XA_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dax_disassociate_entry (void*,struct address_space*,int) ; 
 void* get_unlocked_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unlocked_entry (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  xa_is_value (void*) ; 
 int /*<<< orphan*/  xas ; 
 scalar_t__ xas_get_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_store (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __dax_invalidate_entry(struct address_space *mapping,
					  pgoff_t index, bool trunc)
{
	XA_STATE(xas, &mapping->i_pages, index);
	int ret = 0;
	void *entry;

	xas_lock_irq(&xas);
	entry = get_unlocked_entry(&xas, 0);
	if (!entry || WARN_ON_ONCE(!xa_is_value(entry)))
		goto out;
	if (!trunc &&
	    (xas_get_mark(&xas, PAGECACHE_TAG_DIRTY) ||
	     xas_get_mark(&xas, PAGECACHE_TAG_TOWRITE)))
		goto out;
	dax_disassociate_entry(entry, mapping, trunc);
	xas_store(&xas, NULL);
	mapping->nrexceptional--;
	ret = 1;
out:
	put_unlocked_entry(&xas, entry);
	xas_unlock_irq(&xas);
	return ret;
}