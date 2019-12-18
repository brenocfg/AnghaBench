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
struct extent_buffer {int dummy; } ;
struct btrfs_path {int* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {int /*<<< orphan*/  offset; int /*<<< orphan*/  type; int /*<<< orphan*/  objectid; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_disk_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  btrfs_cpu_key_to_disk (struct btrfs_disk_key*,struct btrfs_key const*) ; 
 int /*<<< orphan*/  btrfs_crit (struct btrfs_fs_info*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_disk_key_objectid (struct btrfs_disk_key*) ; 
 int /*<<< orphan*/  btrfs_disk_key_offset (struct btrfs_disk_key*) ; 
 int /*<<< orphan*/  btrfs_disk_key_type (struct btrfs_disk_key*) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_item_key (struct extent_buffer*,struct btrfs_disk_key*,int) ; 
 int /*<<< orphan*/  btrfs_mark_buffer_dirty (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_print_leaf (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_set_item_key (struct extent_buffer*,struct btrfs_disk_key*,int) ; 
 scalar_t__ comp_keys (struct btrfs_disk_key*,struct btrfs_key const*) ; 
 int /*<<< orphan*/  fixup_low_keys (struct btrfs_path*,struct btrfs_disk_key*,int) ; 
 scalar_t__ unlikely (int) ; 

void btrfs_set_item_key_safe(struct btrfs_fs_info *fs_info,
			     struct btrfs_path *path,
			     const struct btrfs_key *new_key)
{
	struct btrfs_disk_key disk_key;
	struct extent_buffer *eb;
	int slot;

	eb = path->nodes[0];
	slot = path->slots[0];
	if (slot > 0) {
		btrfs_item_key(eb, &disk_key, slot - 1);
		if (unlikely(comp_keys(&disk_key, new_key) >= 0)) {
			btrfs_crit(fs_info,
		"slot %u key (%llu %u %llu) new key (%llu %u %llu)",
				   slot, btrfs_disk_key_objectid(&disk_key),
				   btrfs_disk_key_type(&disk_key),
				   btrfs_disk_key_offset(&disk_key),
				   new_key->objectid, new_key->type,
				   new_key->offset);
			btrfs_print_leaf(eb);
			BUG();
		}
	}
	if (slot < btrfs_header_nritems(eb) - 1) {
		btrfs_item_key(eb, &disk_key, slot + 1);
		if (unlikely(comp_keys(&disk_key, new_key) <= 0)) {
			btrfs_crit(fs_info,
		"slot %u key (%llu %u %llu) new key (%llu %u %llu)",
				   slot, btrfs_disk_key_objectid(&disk_key),
				   btrfs_disk_key_type(&disk_key),
				   btrfs_disk_key_offset(&disk_key),
				   new_key->objectid, new_key->type,
				   new_key->offset);
			btrfs_print_leaf(eb);
			BUG();
		}
	}

	btrfs_cpu_key_to_disk(&disk_key, new_key);
	btrfs_set_item_key(eb, &disk_key, slot);
	btrfs_mark_buffer_dirty(eb);
	if (slot == 0)
		fixup_low_keys(path, &disk_key, 1);
}