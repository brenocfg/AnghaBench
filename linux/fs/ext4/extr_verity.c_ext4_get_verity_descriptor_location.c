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
typedef  int u32 ;
struct inode {int i_blkbits; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
struct ext4_ext_path {size_t p_depth; struct ext4_extent* p_ext; } ;
typedef  int /*<<< orphan*/  desc_size_disk ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*) ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 scalar_t__ EXT_MAX_BLOCKS ; 
 int INT_MAX ; 
 scalar_t__ IS_ERR (struct ext4_ext_path*) ; 
 int PTR_ERR (struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 int ext4_ext_get_actual_len (struct ext4_extent*) ; 
 struct ext4_ext_path* ext4_find_extent (struct inode*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_verity_metadata_pos (struct inode*) ; 
 int /*<<< orphan*/  i_blocksize (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int pagecache_read (struct inode*,int /*<<< orphan*/ *,int,int) ; 
 int round_down (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_get_verity_descriptor_location(struct inode *inode,
					       size_t *desc_size_ret,
					       u64 *desc_pos_ret)
{
	struct ext4_ext_path *path;
	struct ext4_extent *last_extent;
	u32 end_lblk;
	u64 desc_size_pos;
	__le32 desc_size_disk;
	u32 desc_size;
	u64 desc_pos;
	int err;

	/*
	 * Descriptor size is in last 4 bytes of last allocated block.
	 * See ext4_write_verity_descriptor().
	 */

	if (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)) {
		EXT4_ERROR_INODE(inode, "verity file doesn't use extents");
		return -EFSCORRUPTED;
	}

	path = ext4_find_extent(inode, EXT_MAX_BLOCKS - 1, NULL, 0);
	if (IS_ERR(path))
		return PTR_ERR(path);

	last_extent = path[path->p_depth].p_ext;
	if (!last_extent) {
		EXT4_ERROR_INODE(inode, "verity file has no extents");
		ext4_ext_drop_refs(path);
		kfree(path);
		return -EFSCORRUPTED;
	}

	end_lblk = le32_to_cpu(last_extent->ee_block) +
		   ext4_ext_get_actual_len(last_extent);
	desc_size_pos = (u64)end_lblk << inode->i_blkbits;
	ext4_ext_drop_refs(path);
	kfree(path);

	if (desc_size_pos < sizeof(desc_size_disk))
		goto bad;
	desc_size_pos -= sizeof(desc_size_disk);

	err = pagecache_read(inode, &desc_size_disk, sizeof(desc_size_disk),
			     desc_size_pos);
	if (err)
		return err;
	desc_size = le32_to_cpu(desc_size_disk);

	/*
	 * The descriptor is stored just before the desc_size_disk, but starting
	 * on a filesystem block boundary.
	 */

	if (desc_size > INT_MAX || desc_size > desc_size_pos)
		goto bad;

	desc_pos = round_down(desc_size_pos - desc_size, i_blocksize(inode));
	if (desc_pos < ext4_verity_metadata_pos(inode))
		goto bad;

	*desc_size_ret = desc_size;
	*desc_pos_ret = desc_pos;
	return 0;

bad:
	EXT4_ERROR_INODE(inode, "verity file corrupted; can't find descriptor");
	return -EFSCORRUPTED;
}