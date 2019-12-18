#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
struct extent_map {int compress_type; int /*<<< orphan*/  flags; scalar_t__ block_len; void* orig_start; scalar_t__ len; scalar_t__ start; void* block_start; scalar_t__ orig_block_len; void* ram_bytes; int /*<<< orphan*/  bdev; } ;
struct extent_buffer {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {TYPE_2__ root_key; struct btrfs_fs_info* fs_info; } ;
struct btrfs_path {int* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ offset; } ;
struct btrfs_inode {struct btrfs_root* root; } ;
struct btrfs_fs_info {int /*<<< orphan*/  sectorsize; TYPE_1__* fs_devices; } ;
struct btrfs_file_extent_item {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  latest_bdev; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int BTRFS_COMPRESS_NONE ; 
 scalar_t__ BTRFS_FILE_EXTENT_INLINE ; 
 scalar_t__ BTRFS_FILE_EXTENT_PREALLOC ; 
 scalar_t__ BTRFS_FILE_EXTENT_REG ; 
 int /*<<< orphan*/  EXTENT_FLAG_COMPRESSED ; 
 int /*<<< orphan*/  EXTENT_FLAG_PREALLOC ; 
 void* EXTENT_MAP_HOLE ; 
 void* EXTENT_MAP_INLINE ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int btrfs_file_extent_compression (struct extent_buffer*,struct btrfs_file_extent_item*) ; 
 scalar_t__ btrfs_file_extent_disk_bytenr (struct extent_buffer*,struct btrfs_file_extent_item*) ; 
 scalar_t__ btrfs_file_extent_disk_num_bytes (struct extent_buffer*,struct btrfs_file_extent_item*) ; 
 scalar_t__ btrfs_file_extent_num_bytes (struct extent_buffer*,struct btrfs_file_extent_item*) ; 
 scalar_t__ btrfs_file_extent_offset (struct extent_buffer*,struct btrfs_file_extent_item*) ; 
 void* btrfs_file_extent_ram_bytes (struct extent_buffer*,struct btrfs_file_extent_item*) ; 
 scalar_t__ btrfs_file_extent_type (struct extent_buffer*,struct btrfs_file_extent_item*) ; 
 int /*<<< orphan*/  btrfs_ino (struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int const) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void btrfs_extent_item_to_extent_map(struct btrfs_inode *inode,
				     const struct btrfs_path *path,
				     struct btrfs_file_extent_item *fi,
				     const bool new_inline,
				     struct extent_map *em)
{
	struct btrfs_fs_info *fs_info = inode->root->fs_info;
	struct btrfs_root *root = inode->root;
	struct extent_buffer *leaf = path->nodes[0];
	const int slot = path->slots[0];
	struct btrfs_key key;
	u64 extent_start, extent_end;
	u64 bytenr;
	u8 type = btrfs_file_extent_type(leaf, fi);
	int compress_type = btrfs_file_extent_compression(leaf, fi);

	em->bdev = fs_info->fs_devices->latest_bdev;
	btrfs_item_key_to_cpu(leaf, &key, slot);
	extent_start = key.offset;

	if (type == BTRFS_FILE_EXTENT_REG ||
	    type == BTRFS_FILE_EXTENT_PREALLOC) {
		extent_end = extent_start +
			btrfs_file_extent_num_bytes(leaf, fi);
	} else if (type == BTRFS_FILE_EXTENT_INLINE) {
		size_t size;
		size = btrfs_file_extent_ram_bytes(leaf, fi);
		extent_end = ALIGN(extent_start + size,
				   fs_info->sectorsize);
	}

	em->ram_bytes = btrfs_file_extent_ram_bytes(leaf, fi);
	if (type == BTRFS_FILE_EXTENT_REG ||
	    type == BTRFS_FILE_EXTENT_PREALLOC) {
		em->start = extent_start;
		em->len = extent_end - extent_start;
		em->orig_start = extent_start -
			btrfs_file_extent_offset(leaf, fi);
		em->orig_block_len = btrfs_file_extent_disk_num_bytes(leaf, fi);
		bytenr = btrfs_file_extent_disk_bytenr(leaf, fi);
		if (bytenr == 0) {
			em->block_start = EXTENT_MAP_HOLE;
			return;
		}
		if (compress_type != BTRFS_COMPRESS_NONE) {
			set_bit(EXTENT_FLAG_COMPRESSED, &em->flags);
			em->compress_type = compress_type;
			em->block_start = bytenr;
			em->block_len = em->orig_block_len;
		} else {
			bytenr += btrfs_file_extent_offset(leaf, fi);
			em->block_start = bytenr;
			em->block_len = em->len;
			if (type == BTRFS_FILE_EXTENT_PREALLOC)
				set_bit(EXTENT_FLAG_PREALLOC, &em->flags);
		}
	} else if (type == BTRFS_FILE_EXTENT_INLINE) {
		em->block_start = EXTENT_MAP_INLINE;
		em->start = extent_start;
		em->len = extent_end - extent_start;
		/*
		 * Initialize orig_start and block_len with the same values
		 * as in inode.c:btrfs_get_extent().
		 */
		em->orig_start = EXTENT_MAP_HOLE;
		em->block_len = (u64)-1;
		if (!new_inline && compress_type != BTRFS_COMPRESS_NONE) {
			set_bit(EXTENT_FLAG_COMPRESSED, &em->flags);
			em->compress_type = compress_type;
		}
	} else {
		btrfs_err(fs_info,
			  "unknown file extent item type %d, inode %llu, offset %llu, "
			  "root %llu", type, btrfs_ino(inode), extent_start,
			  root->root_key.objectid);
	}
}