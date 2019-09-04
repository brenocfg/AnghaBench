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
struct extent_buffer {int dummy; } ;
struct btrfs_key {int dummy; } ;
struct btrfs_fs_info {scalar_t__ last_trans_committed; } ;

/* Variables and functions */
 int EIO ; 
 int btrfs_comp_cpu_keys (struct btrfs_key*,struct btrfs_key*) ; 
 scalar_t__ btrfs_header_generation (struct extent_buffer*) ; 
 int btrfs_header_level (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_node_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int verify_level_key(struct btrfs_fs_info *fs_info,
			    struct extent_buffer *eb, int level,
			    struct btrfs_key *first_key, u64 parent_transid)
{
	int found_level;
	struct btrfs_key found_key;
	int ret;

	found_level = btrfs_header_level(eb);
	if (found_level != level) {
#ifdef CONFIG_BTRFS_DEBUG
		WARN_ON(1);
		btrfs_err(fs_info,
"tree level mismatch detected, bytenr=%llu level expected=%u has=%u",
			  eb->start, level, found_level);
#endif
		return -EIO;
	}

	if (!first_key)
		return 0;

	/*
	 * For live tree block (new tree blocks in current transaction),
	 * we need proper lock context to avoid race, which is impossible here.
	 * So we only checks tree blocks which is read from disk, whose
	 * generation <= fs_info->last_trans_committed.
	 */
	if (btrfs_header_generation(eb) > fs_info->last_trans_committed)
		return 0;
	if (found_level)
		btrfs_node_key_to_cpu(eb, &found_key, 0);
	else
		btrfs_item_key_to_cpu(eb, &found_key, 0);
	ret = btrfs_comp_cpu_keys(first_key, &found_key);

#ifdef CONFIG_BTRFS_DEBUG
	if (ret) {
		WARN_ON(1);
		btrfs_err(fs_info,
"tree first key mismatch detected, bytenr=%llu parent_transid=%llu key expected=(%llu,%u,%llu) has=(%llu,%u,%llu)",
			  eb->start, parent_transid, first_key->objectid,
			  first_key->type, first_key->offset,
			  found_key.objectid, found_key.type,
			  found_key.offset);
	}
#endif
	return ret;
}