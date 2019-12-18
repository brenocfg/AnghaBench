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
struct extent_buffer {int /*<<< orphan*/  bflags; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  EXTENT_BUFFER_CORRUPT ; 
 int /*<<< orphan*/  EXTENT_BUFFER_READAHEAD ; 
 scalar_t__ IS_ERR (struct extent_buffer*) ; 
 int /*<<< orphan*/  WAIT_PAGE_LOCK ; 
 struct extent_buffer* btrfs_find_create_tree_block (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ extent_buffer_uptodate (struct extent_buffer*) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 int /*<<< orphan*/  free_extent_buffer_stale (struct extent_buffer*) ; 
 int read_extent_buffer_pages (struct extent_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reada_tree_block_flagged(struct btrfs_fs_info *fs_info, u64 bytenr,
				    int mirror_num, struct extent_buffer **eb)
{
	struct extent_buffer *buf = NULL;
	int ret;

	buf = btrfs_find_create_tree_block(fs_info, bytenr);
	if (IS_ERR(buf))
		return 0;

	set_bit(EXTENT_BUFFER_READAHEAD, &buf->bflags);

	ret = read_extent_buffer_pages(buf, WAIT_PAGE_LOCK, mirror_num);
	if (ret) {
		free_extent_buffer_stale(buf);
		return ret;
	}

	if (test_bit(EXTENT_BUFFER_CORRUPT, &buf->bflags)) {
		free_extent_buffer_stale(buf);
		return -EIO;
	} else if (extent_buffer_uptodate(buf)) {
		*eb = buf;
	} else {
		free_extent_buffer(buf);
	}
	return 0;
}