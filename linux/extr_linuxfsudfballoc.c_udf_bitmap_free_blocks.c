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
typedef  scalar_t__ uint32_t ;
struct udf_sb_info {int /*<<< orphan*/  s_alloc_mutex; int /*<<< orphan*/  s_partition; struct udf_part_map* s_partmaps; } ;
struct udf_part_map {scalar_t__ s_partition_len; } ;
struct udf_bitmap {struct buffer_head** s_block_bitmap; } ;
struct super_block {int s_blocksize_bits; int s_blocksize; } ;
struct spaceBitmapDesc {int dummy; } ;
struct kernel_lb_addr {size_t partitionReferenceNum; scalar_t__ logicalBlockNum; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  unsigned long __u8 ;

/* Variables and functions */
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int load_block_bitmap (struct super_block*,struct udf_bitmap*,unsigned long) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udf_add_free_space (struct super_block*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  udf_debug (char*,unsigned long,...) ; 
 scalar_t__ udf_set_bit (unsigned long,scalar_t__) ; 

__attribute__((used)) static void udf_bitmap_free_blocks(struct super_block *sb,
				   struct udf_bitmap *bitmap,
				   struct kernel_lb_addr *bloc,
				   uint32_t offset,
				   uint32_t count)
{
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct buffer_head *bh = NULL;
	struct udf_part_map *partmap;
	unsigned long block;
	unsigned long block_group;
	unsigned long bit;
	unsigned long i;
	int bitmap_nr;
	unsigned long overflow;

	mutex_lock(&sbi->s_alloc_mutex);
	partmap = &sbi->s_partmaps[bloc->partitionReferenceNum];
	if (bloc->logicalBlockNum + count < count ||
	    (bloc->logicalBlockNum + count) > partmap->s_partition_len) {
		udf_debug("%u < %d || %u + %u > %u\n",
			  bloc->logicalBlockNum, 0,
			  bloc->logicalBlockNum, count,
			  partmap->s_partition_len);
		goto error_return;
	}

	block = bloc->logicalBlockNum + offset +
		(sizeof(struct spaceBitmapDesc) << 3);

	do {
		overflow = 0;
		block_group = block >> (sb->s_blocksize_bits + 3);
		bit = block % (sb->s_blocksize << 3);

		/*
		* Check to see if we are freeing blocks across a group boundary.
		*/
		if (bit + count > (sb->s_blocksize << 3)) {
			overflow = bit + count - (sb->s_blocksize << 3);
			count -= overflow;
		}
		bitmap_nr = load_block_bitmap(sb, bitmap, block_group);
		if (bitmap_nr < 0)
			goto error_return;

		bh = bitmap->s_block_bitmap[bitmap_nr];
		for (i = 0; i < count; i++) {
			if (udf_set_bit(bit + i, bh->b_data)) {
				udf_debug("bit %lu already set\n", bit + i);
				udf_debug("byte=%2x\n",
					  ((__u8 *)bh->b_data)[(bit + i) >> 3]);
			}
		}
		udf_add_free_space(sb, sbi->s_partition, count);
		mark_buffer_dirty(bh);
		if (overflow) {
			block += count;
			count = overflow;
		}
	} while (overflow);

error_return:
	mutex_unlock(&sbi->s_alloc_mutex);
}