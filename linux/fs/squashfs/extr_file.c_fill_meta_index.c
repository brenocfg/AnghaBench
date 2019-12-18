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
typedef  long long u64 ;
struct squashfs_sb_info {int block_log; long long inode_table; } ;
struct meta_index {int offset; int entries; struct meta_entry* meta_entry; scalar_t__ inode_number; } ;
struct meta_entry {long long index_block; int offset; long long data_block; } ;
struct inode {TYPE_2__* i_sb; } ;
struct TYPE_4__ {struct squashfs_sb_info* s_fs_info; } ;
struct TYPE_3__ {long long block_list_start; int offset; long long start; } ;

/* Variables and functions */
 int SQUASHFS_META_ENTRIES ; 
 int SQUASHFS_META_INDEXES ; 
 int /*<<< orphan*/  TRACE (char*,int,int,...) ; 
 int calculate_skip (int) ; 
 struct meta_index* empty_meta_index (struct inode*,int,int) ; 
 int i_size_read (struct inode*) ; 
 struct meta_index* locate_meta_index (struct inode*,int,int) ; 
 long long read_indexes (TYPE_2__*,int,long long*,int*) ; 
 int /*<<< orphan*/  release_meta_index (struct inode*,struct meta_index*) ; 
 TYPE_1__* squashfs_i (struct inode*) ; 

__attribute__((used)) static int fill_meta_index(struct inode *inode, int index,
		u64 *index_block, int *index_offset, u64 *data_block)
{
	struct squashfs_sb_info *msblk = inode->i_sb->s_fs_info;
	int skip = calculate_skip(i_size_read(inode) >> msblk->block_log);
	int offset = 0;
	struct meta_index *meta;
	struct meta_entry *meta_entry;
	u64 cur_index_block = squashfs_i(inode)->block_list_start;
	int cur_offset = squashfs_i(inode)->offset;
	u64 cur_data_block = squashfs_i(inode)->start;
	int err, i;

	/*
	 * Scale index to cache index (cache slot entry)
	 */
	index /= SQUASHFS_META_INDEXES * skip;

	while (offset < index) {
		meta = locate_meta_index(inode, offset + 1, index);

		if (meta == NULL) {
			meta = empty_meta_index(inode, offset + 1, skip);
			if (meta == NULL)
				goto all_done;
		} else {
			offset = index < meta->offset + meta->entries ? index :
				meta->offset + meta->entries - 1;
			meta_entry = &meta->meta_entry[offset - meta->offset];
			cur_index_block = meta_entry->index_block +
				msblk->inode_table;
			cur_offset = meta_entry->offset;
			cur_data_block = meta_entry->data_block;
			TRACE("get_meta_index: offset %d, meta->offset %d, "
				"meta->entries %d\n", offset, meta->offset,
				meta->entries);
			TRACE("get_meta_index: index_block 0x%llx, offset 0x%x"
				" data_block 0x%llx\n", cur_index_block,
				cur_offset, cur_data_block);
		}

		/*
		 * If necessary grow cache slot by reading block list.  Cache
		 * slot is extended up to index or to the end of the slot, in
		 * which case further slots will be used.
		 */
		for (i = meta->offset + meta->entries; i <= index &&
				i < meta->offset + SQUASHFS_META_ENTRIES; i++) {
			int blocks = skip * SQUASHFS_META_INDEXES;
			long long res = read_indexes(inode->i_sb, blocks,
					&cur_index_block, &cur_offset);

			if (res < 0) {
				if (meta->entries == 0)
					/*
					 * Don't leave an empty slot on read
					 * error allocated to this inode...
					 */
					meta->inode_number = 0;
				err = res;
				goto failed;
			}

			cur_data_block += res;
			meta_entry = &meta->meta_entry[i - meta->offset];
			meta_entry->index_block = cur_index_block -
				msblk->inode_table;
			meta_entry->offset = cur_offset;
			meta_entry->data_block = cur_data_block;
			meta->entries++;
			offset++;
		}

		TRACE("get_meta_index: meta->offset %d, meta->entries %d\n",
				meta->offset, meta->entries);

		release_meta_index(inode, meta);
	}

all_done:
	*index_block = cur_index_block;
	*index_offset = cur_offset;
	*data_block = cur_data_block;

	/*
	 * Scale cache index (cache slot entry) to index
	 */
	return offset * SQUASHFS_META_INDEXES * skip;

failed:
	release_meta_index(inode, meta);
	return err;
}