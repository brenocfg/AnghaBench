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
struct tree_mod_elem {scalar_t__ op; scalar_t__ slot; } ;
struct extent_buffer {int /*<<< orphan*/  start; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_NODEPTRS_PER_BLOCK (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ MOD_LOG_KEY_REMOVE_WHILE_FREEING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __tree_mod_log_rewind (struct btrfs_fs_info*,struct extent_buffer*,int /*<<< orphan*/ ,struct tree_mod_elem*) ; 
 struct extent_buffer* alloc_dummy_extent_buffer (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 struct extent_buffer* btrfs_clone_extent_buffer (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_header_backref_rev (struct extent_buffer*) ; 
 scalar_t__ btrfs_header_level (struct extent_buffer*) ; 
 scalar_t__ btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_header_owner (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_set_header_backref_rev (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_header_bytenr (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_header_level (struct extent_buffer*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_set_header_owner (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_lock_blocking_read (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_set_path_blocking (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_tree_read_lock (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_read_unlock_blocking (struct extent_buffer*) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 struct tree_mod_elem* tree_mod_log_search (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct extent_buffer *
tree_mod_log_rewind(struct btrfs_fs_info *fs_info, struct btrfs_path *path,
		    struct extent_buffer *eb, u64 time_seq)
{
	struct extent_buffer *eb_rewin;
	struct tree_mod_elem *tm;

	if (!time_seq)
		return eb;

	if (btrfs_header_level(eb) == 0)
		return eb;

	tm = tree_mod_log_search(fs_info, eb->start, time_seq);
	if (!tm)
		return eb;

	btrfs_set_path_blocking(path);
	btrfs_set_lock_blocking_read(eb);

	if (tm->op == MOD_LOG_KEY_REMOVE_WHILE_FREEING) {
		BUG_ON(tm->slot != 0);
		eb_rewin = alloc_dummy_extent_buffer(fs_info, eb->start);
		if (!eb_rewin) {
			btrfs_tree_read_unlock_blocking(eb);
			free_extent_buffer(eb);
			return NULL;
		}
		btrfs_set_header_bytenr(eb_rewin, eb->start);
		btrfs_set_header_backref_rev(eb_rewin,
					     btrfs_header_backref_rev(eb));
		btrfs_set_header_owner(eb_rewin, btrfs_header_owner(eb));
		btrfs_set_header_level(eb_rewin, btrfs_header_level(eb));
	} else {
		eb_rewin = btrfs_clone_extent_buffer(eb);
		if (!eb_rewin) {
			btrfs_tree_read_unlock_blocking(eb);
			free_extent_buffer(eb);
			return NULL;
		}
	}

	btrfs_tree_read_unlock_blocking(eb);
	free_extent_buffer(eb);

	btrfs_tree_read_lock(eb_rewin);
	__tree_mod_log_rewind(fs_info, eb_rewin, time_seq, tm);
	WARN_ON(btrfs_header_nritems(eb_rewin) >
		BTRFS_NODEPTRS_PER_BLOCK(fs_info));

	return eb_rewin;
}