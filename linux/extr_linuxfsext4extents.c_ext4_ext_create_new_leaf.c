#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
struct ext4_ext_path {TYPE_1__* p_hdr; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  ext4_lblk_t ;
struct TYPE_2__ {scalar_t__ eh_entries; scalar_t__ eh_max; } ;

/* Variables and functions */
 scalar_t__ EXT_HAS_FREE_INDEX (struct ext4_ext_path*) ; 
 scalar_t__ IS_ERR (struct ext4_ext_path*) ; 
 int PTR_ERR (struct ext4_ext_path*) ; 
 int ext4_ext_grow_indepth (int /*<<< orphan*/ *,struct inode*,unsigned int) ; 
 int ext4_ext_split (int /*<<< orphan*/ *,struct inode*,unsigned int,struct ext4_ext_path*,struct ext4_extent*,int) ; 
 struct ext4_ext_path* ext4_find_extent (struct inode*,int /*<<< orphan*/ ,struct ext4_ext_path**,unsigned int) ; 
 int ext_depth (struct inode*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_ext_create_new_leaf(handle_t *handle, struct inode *inode,
				    unsigned int mb_flags,
				    unsigned int gb_flags,
				    struct ext4_ext_path **ppath,
				    struct ext4_extent *newext)
{
	struct ext4_ext_path *path = *ppath;
	struct ext4_ext_path *curp;
	int depth, i, err = 0;

repeat:
	i = depth = ext_depth(inode);

	/* walk up to the tree and look for free index entry */
	curp = path + depth;
	while (i > 0 && !EXT_HAS_FREE_INDEX(curp)) {
		i--;
		curp--;
	}

	/* we use already allocated block for index block,
	 * so subsequent data blocks should be contiguous */
	if (EXT_HAS_FREE_INDEX(curp)) {
		/* if we found index with free entry, then use that
		 * entry: create all needed subtree and add new leaf */
		err = ext4_ext_split(handle, inode, mb_flags, path, newext, i);
		if (err)
			goto out;

		/* refill path */
		path = ext4_find_extent(inode,
				    (ext4_lblk_t)le32_to_cpu(newext->ee_block),
				    ppath, gb_flags);
		if (IS_ERR(path))
			err = PTR_ERR(path);
	} else {
		/* tree is full, time to grow in depth */
		err = ext4_ext_grow_indepth(handle, inode, mb_flags);
		if (err)
			goto out;

		/* refill path */
		path = ext4_find_extent(inode,
				   (ext4_lblk_t)le32_to_cpu(newext->ee_block),
				    ppath, gb_flags);
		if (IS_ERR(path)) {
			err = PTR_ERR(path);
			goto out;
		}

		/*
		 * only first (depth 0 -> 1) produces free space;
		 * in all other cases we have to split the grown tree
		 */
		depth = ext_depth(inode);
		if (path[depth].p_hdr->eh_entries == path[depth].p_hdr->eh_max) {
			/* now we need to split */
			goto repeat;
		}
	}

out:
	return err;
}