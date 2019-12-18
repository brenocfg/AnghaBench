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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_sb_info {int dummy; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
struct ext4_ext_path {struct ext4_extent* p_ext; int /*<<< orphan*/  p_block; } ;
typedef  scalar_t__ ext4_lblk_t ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 scalar_t__ EXT4_B2C (struct ext4_sb_info*,scalar_t__) ; 
 scalar_t__ EXT4_C2B (struct ext4_sb_info*,scalar_t__) ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*,unsigned long,int,int /*<<< orphan*/ ) ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct ext4_ext_path*) ; 
 int PTR_ERR (struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 scalar_t__ ext4_ext_get_actual_len (struct ext4_extent*) ; 
 scalar_t__ ext4_ext_next_allocated_block (struct ext4_ext_path*) ; 
 struct ext4_ext_path* ext4_find_extent (struct inode*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ext_depth (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int ext4_clu_mapped(struct inode *inode, ext4_lblk_t lclu)
{
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	struct ext4_ext_path *path;
	int depth, mapped = 0, err = 0;
	struct ext4_extent *extent;
	ext4_lblk_t first_lblk, first_lclu, last_lclu;

	/* search for the extent closest to the first block in the cluster */
	path = ext4_find_extent(inode, EXT4_C2B(sbi, lclu), NULL, 0);
	if (IS_ERR(path)) {
		err = PTR_ERR(path);
		path = NULL;
		goto out;
	}

	depth = ext_depth(inode);

	/*
	 * A consistent leaf must not be empty.  This situation is possible,
	 * though, _during_ tree modification, and it's why an assert can't
	 * be put in ext4_find_extent().
	 */
	if (unlikely(path[depth].p_ext == NULL && depth != 0)) {
		EXT4_ERROR_INODE(inode,
		    "bad extent address - lblock: %lu, depth: %d, pblock: %lld",
				 (unsigned long) EXT4_C2B(sbi, lclu),
				 depth, path[depth].p_block);
		err = -EFSCORRUPTED;
		goto out;
	}

	extent = path[depth].p_ext;

	/* can't be mapped if the extent tree is empty */
	if (extent == NULL)
		goto out;

	first_lblk = le32_to_cpu(extent->ee_block);
	first_lclu = EXT4_B2C(sbi, first_lblk);

	/*
	 * Three possible outcomes at this point - found extent spanning
	 * the target cluster, to the left of the target cluster, or to the
	 * right of the target cluster.  The first two cases are handled here.
	 * The last case indicates the target cluster is not mapped.
	 */
	if (lclu >= first_lclu) {
		last_lclu = EXT4_B2C(sbi, first_lblk +
				     ext4_ext_get_actual_len(extent) - 1);
		if (lclu <= last_lclu) {
			mapped = 1;
		} else {
			first_lblk = ext4_ext_next_allocated_block(path);
			first_lclu = EXT4_B2C(sbi, first_lblk);
			if (lclu == first_lclu)
				mapped = 1;
		}
	}

out:
	ext4_ext_drop_refs(path);
	kfree(path);

	return err ? err : mapped;
}