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
struct super_block {struct squashfs_sb_info* s_fs_info; } ;
struct squashfs_sb_info {unsigned int fragments; int /*<<< orphan*/ * fragment_index; } ;
struct squashfs_fragment_entry {int /*<<< orphan*/  size; int /*<<< orphan*/  start_block; } ;
typedef  int /*<<< orphan*/  fragment_entry ;

/* Variables and functions */
 int EIO ; 
 int SQUASHFS_FRAGMENT_INDEX (unsigned int) ; 
 int SQUASHFS_FRAGMENT_INDEX_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int squashfs_block_size (int /*<<< orphan*/ ) ; 
 int squashfs_read_metadata (struct super_block*,struct squashfs_fragment_entry*,int /*<<< orphan*/ *,int*,int) ; 

int squashfs_frag_lookup(struct super_block *sb, unsigned int fragment,
				u64 *fragment_block)
{
	struct squashfs_sb_info *msblk = sb->s_fs_info;
	int block, offset, size;
	struct squashfs_fragment_entry fragment_entry;
	u64 start_block;

	if (fragment >= msblk->fragments)
		return -EIO;
	block = SQUASHFS_FRAGMENT_INDEX(fragment);
	offset = SQUASHFS_FRAGMENT_INDEX_OFFSET(fragment);

	start_block = le64_to_cpu(msblk->fragment_index[block]);

	size = squashfs_read_metadata(sb, &fragment_entry, &start_block,
					&offset, sizeof(fragment_entry));
	if (size < 0)
		return size;

	*fragment_block = le64_to_cpu(fragment_entry.start_block);
	return squashfs_block_size(fragment_entry.size);
}