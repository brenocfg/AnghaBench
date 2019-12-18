#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct page {scalar_t__ private; } ;
struct extent_buffer {int /*<<< orphan*/  start; struct page** pages; } ;
struct btrfs_fs_info {TYPE_1__* fs_devices; int /*<<< orphan*/  super_copy; } ;
struct TYPE_2__ {int /*<<< orphan*/  metadata_uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BTRFS_CSUM_SIZE ; 
 int /*<<< orphan*/  BTRFS_FSID_SIZE ; 
 int EINVAL ; 
 int EUCLEAN ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 scalar_t__ WARN_ON (int) ; 
 int btrfs_check_leaf_full (struct extent_buffer*) ; 
 int btrfs_check_node (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_header_bytenr (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_header_fsid () ; 
 scalar_t__ btrfs_header_level (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_super_csum_size (int /*<<< orphan*/ ) ; 
 scalar_t__ csum_tree_block (struct extent_buffer*,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp_extent_buffer (struct extent_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ page_offset (struct page*) ; 
 int /*<<< orphan*/  write_extent_buffer (struct extent_buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int csum_dirty_buffer(struct btrfs_fs_info *fs_info, struct page *page)
{
	u64 start = page_offset(page);
	u64 found_start;
	u8 result[BTRFS_CSUM_SIZE];
	u16 csum_size = btrfs_super_csum_size(fs_info->super_copy);
	struct extent_buffer *eb;
	int ret;

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

	ASSERT(memcmp_extent_buffer(eb, fs_info->fs_devices->metadata_uuid,
			btrfs_header_fsid(), BTRFS_FSID_SIZE) == 0);

	if (csum_tree_block(eb, result))
		return -EINVAL;

	if (btrfs_header_level(eb))
		ret = btrfs_check_node(eb);
	else
		ret = btrfs_check_leaf_full(eb);

	if (ret < 0) {
		btrfs_err(fs_info,
		"block=%llu write time tree block corruption detected",
			  eb->start);
		return ret;
	}
	write_extent_buffer(eb, result, 0, csum_size);

	return 0;
}