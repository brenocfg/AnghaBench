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
struct page {int dummy; } ;
struct address_space {int dummy; } ;
typedef  enum migrate_mode { ____Placeholder_migrate_mode } migrate_mode ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  MIGRATE_SYNC 129 
#define  MIGRATE_SYNC_NO_COPY 128 
 scalar_t__ PageDirty (struct page*) ; 
 int migrate_page (struct address_space*,struct page*,struct page*,int) ; 
 scalar_t__ page_has_private (struct page*) ; 
 int /*<<< orphan*/  try_to_release_page (struct page*,int /*<<< orphan*/ ) ; 
 int writeout (struct address_space*,struct page*) ; 

__attribute__((used)) static int fallback_migrate_page(struct address_space *mapping,
	struct page *newpage, struct page *page, enum migrate_mode mode)
{
	if (PageDirty(page)) {
		/* Only writeback pages in full synchronous migration */
		switch (mode) {
		case MIGRATE_SYNC:
		case MIGRATE_SYNC_NO_COPY:
			break;
		default:
			return -EBUSY;
		}
		return writeout(mapping, page);
	}

	/*
	 * Buffers may be managed in a filesystem specific way.
	 * We must have no buffers or drop them.
	 */
	if (page_has_private(page) &&
	    !try_to_release_page(page, GFP_KERNEL))
		return mode == MIGRATE_SYNC ? -EAGAIN : -EBUSY;

	return migrate_page(mapping, newpage, page, mode);
}