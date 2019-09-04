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
typedef  int u64 ;
struct super_block {struct squashfs_sb_info* s_fs_info; } ;
struct squashfs_sb_info {int directory_table; } ;
struct squashfs_dir_index {int /*<<< orphan*/  start_block; int /*<<< orphan*/  size; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  dir_index ;

/* Variables and functions */
 int SQUASHFS_METADATA_SIZE ; 
 unsigned int SQUASHFS_NAME_LEN ; 
 int /*<<< orphan*/  TRACE (char*,int,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int squashfs_read_metadata (struct super_block*,struct squashfs_dir_index*,int*,int*,unsigned int) ; 

__attribute__((used)) static int get_dir_index_using_offset(struct super_block *sb,
	u64 *next_block, int *next_offset, u64 index_start, int index_offset,
	int i_count, u64 f_pos)
{
	struct squashfs_sb_info *msblk = sb->s_fs_info;
	int err, i, index, length = 0;
	unsigned int size;
	struct squashfs_dir_index dir_index;

	TRACE("Entered get_dir_index_using_offset, i_count %d, f_pos %lld\n",
					i_count, f_pos);

	/*
	 * Translate from external f_pos to the internal f_pos.  This
	 * is offset by 3 because we invent "." and ".." entries which are
	 * not actually stored in the directory.
	 */
	if (f_pos <= 3)
		return f_pos;
	f_pos -= 3;

	for (i = 0; i < i_count; i++) {
		err = squashfs_read_metadata(sb, &dir_index, &index_start,
				&index_offset, sizeof(dir_index));
		if (err < 0)
			break;

		index = le32_to_cpu(dir_index.index);
		if (index > f_pos)
			/*
			 * Found the index we're looking for.
			 */
			break;

		size = le32_to_cpu(dir_index.size) + 1;

		/* size should never be larger than SQUASHFS_NAME_LEN */
		if (size > SQUASHFS_NAME_LEN)
			break;

		err = squashfs_read_metadata(sb, NULL, &index_start,
				&index_offset, size);
		if (err < 0)
			break;

		length = index;
		*next_block = le32_to_cpu(dir_index.start_block) +
					msblk->directory_table;
	}

	*next_offset = (length + *next_offset) % SQUASHFS_METADATA_SIZE;

	/*
	 * Translate back from internal f_pos to external f_pos.
	 */
	return length + 3;
}