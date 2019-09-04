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
typedef  scalar_t__ u64 ;
struct page {scalar_t__ private; } ;
struct extent_buffer {struct page** pages; } ;
struct btrfs_fs_info {int /*<<< orphan*/  fsid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BTRFS_FSID_SIZE ; 
 int EUCLEAN ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ btrfs_header_bytenr (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_header_fsid () ; 
 int csum_tree_block (struct btrfs_fs_info*,struct extent_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp_extent_buffer (struct extent_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ page_offset (struct page*) ; 

__attribute__((used)) static int csum_dirty_buffer(struct btrfs_fs_info *fs_info, struct page *page)
{
	u64 start = page_offset(page);
	u64 found_start;
	struct extent_buffer *eb;

	eb = (struct extent_buffer *)page->private;
	if (page != eb->pages[0])
		return 0;

	found_start = btrfs_header_bytenr(eb);
	/*
	 * Please do not consolidate these warnings into a single if.
	 * It is useful to know what went wrong.
	 */
	if (WARN_ON(found_start != start))
		return -EUCLEAN;
	if (WARN_ON(!PageUptodate(page)))
		return -EUCLEAN;

	ASSERT(memcmp_extent_buffer(eb, fs_info->fsid,
			btrfs_header_fsid(), BTRFS_FSID_SIZE) == 0);

	return csum_tree_block(fs_info, eb, 0);
}