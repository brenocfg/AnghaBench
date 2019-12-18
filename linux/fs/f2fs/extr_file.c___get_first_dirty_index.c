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
struct page {int /*<<< orphan*/  index; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int SEEK_DATA ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 int find_get_pages_tag (struct address_space*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct page**) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static pgoff_t __get_first_dirty_index(struct address_space *mapping,
						pgoff_t pgofs, int whence)
{
	struct page *page;
	int nr_pages;

	if (whence != SEEK_DATA)
		return 0;

	/* find first dirty page index */
	nr_pages = find_get_pages_tag(mapping, &pgofs, PAGECACHE_TAG_DIRTY,
				      1, &page);
	if (!nr_pages)
		return ULONG_MAX;
	pgofs = page->index;
	put_page(page);
	return pgofs;
}