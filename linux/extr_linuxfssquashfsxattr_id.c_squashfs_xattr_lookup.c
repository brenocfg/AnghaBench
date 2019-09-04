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
typedef  void* u64 ;
struct super_block {struct squashfs_sb_info* s_fs_info; } ;
struct squashfs_xattr_id {int /*<<< orphan*/  count; int /*<<< orphan*/  size; int /*<<< orphan*/  xattr; } ;
struct squashfs_sb_info {int /*<<< orphan*/ * xattr_id_table; } ;
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */
 int SQUASHFS_XATTR_BLOCK (unsigned int) ; 
 int SQUASHFS_XATTR_BLOCK_OFFSET (unsigned int) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int squashfs_read_metadata (struct super_block*,struct squashfs_xattr_id*,void**,int*,int) ; 

int squashfs_xattr_lookup(struct super_block *sb, unsigned int index,
		int *count, unsigned int *size, unsigned long long *xattr)
{
	struct squashfs_sb_info *msblk = sb->s_fs_info;
	int block = SQUASHFS_XATTR_BLOCK(index);
	int offset = SQUASHFS_XATTR_BLOCK_OFFSET(index);
	u64 start_block = le64_to_cpu(msblk->xattr_id_table[block]);
	struct squashfs_xattr_id id;
	int err;

	err = squashfs_read_metadata(sb, &id, &start_block, &offset,
							sizeof(id));
	if (err < 0)
		return err;

	*xattr = le64_to_cpu(id.xattr);
	*size = le32_to_cpu(id.size);
	*count = le32_to_cpu(id.count);
	return 0;
}