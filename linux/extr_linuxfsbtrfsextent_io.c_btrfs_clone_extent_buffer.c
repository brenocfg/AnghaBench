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
struct extent_buffer {int /*<<< orphan*/  bflags; struct page** pages; int /*<<< orphan*/  len; int /*<<< orphan*/  start; int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_BUFFER_UNMAPPED ; 
 int /*<<< orphan*/  EXTENT_BUFFER_UPTODATE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct extent_buffer* __alloc_extent_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attach_extent_buffer_page (struct extent_buffer*,struct page*) ; 
 int /*<<< orphan*/  btrfs_release_extent_buffer (struct extent_buffer*) ; 
 int /*<<< orphan*/  copy_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int num_extent_pages (struct extent_buffer*) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct extent_buffer *btrfs_clone_extent_buffer(struct extent_buffer *src)
{
	int i;
	struct page *p;
	struct extent_buffer *new;
	int num_pages = num_extent_pages(src);

	new = __alloc_extent_buffer(src->fs_info, src->start, src->len);
	if (new == NULL)
		return NULL;

	for (i = 0; i < num_pages; i++) {
		p = alloc_page(GFP_NOFS);
		if (!p) {
			btrfs_release_extent_buffer(new);
			return NULL;
		}
		attach_extent_buffer_page(new, p);
		WARN_ON(PageDirty(p));
		SetPageUptodate(p);
		new->pages[i] = p;
		copy_page(page_address(p), page_address(src->pages[i]));
	}

	set_bit(EXTENT_BUFFER_UPTODATE, &new->bflags);
	set_bit(EXTENT_BUFFER_UNMAPPED, &new->bflags);

	return new;
}