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
typedef  int /*<<< orphan*/  u64 ;
struct extent_buffer {int /*<<< orphan*/ * pages; int /*<<< orphan*/  bflags; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_BUFFER_UNMAPPED ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct extent_buffer* __alloc_extent_buffer (struct btrfs_fs_info*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  __free_extent_buffer (struct extent_buffer*) ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_header_nritems (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int num_extent_pages (struct extent_buffer*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_extent_buffer_uptodate (struct extent_buffer*) ; 

struct extent_buffer *__alloc_dummy_extent_buffer(struct btrfs_fs_info *fs_info,
						  u64 start, unsigned long len)
{
	struct extent_buffer *eb;
	int num_pages;
	int i;

	eb = __alloc_extent_buffer(fs_info, start, len);
	if (!eb)
		return NULL;

	num_pages = num_extent_pages(eb);
	for (i = 0; i < num_pages; i++) {
		eb->pages[i] = alloc_page(GFP_NOFS);
		if (!eb->pages[i])
			goto err;
	}
	set_extent_buffer_uptodate(eb);
	btrfs_set_header_nritems(eb, 0);
	set_bit(EXTENT_BUFFER_UNMAPPED, &eb->bflags);

	return eb;
err:
	for (; i > 0; i--)
		__free_page(eb->pages[i - 1]);
	__free_extent_buffer(eb);
	return NULL;
}