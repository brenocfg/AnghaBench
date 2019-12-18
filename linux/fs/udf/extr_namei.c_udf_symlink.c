#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ udf_pblk_t ;
struct TYPE_12__ {int /*<<< orphan*/ * i_data; } ;
struct TYPE_11__ {int /*<<< orphan*/  partitionReferenceNum; int /*<<< orphan*/  logicalBlockNum; } ;
struct udf_inode_info {scalar_t__ i_alloc_type; int i_lenExtents; int i_lenEAttr; int i_lenAlloc; int /*<<< orphan*/  i_data_sem; TYPE_3__ i_ext; TYPE_2__ i_location; } ;
struct super_block {int s_blocksize; } ;
struct pathComponent {int componentType; int lengthComponentIdent; int /*<<< orphan*/  componentIdent; scalar_t__ componentFileVersionNum; } ;
struct kernel_lb_addr {int /*<<< orphan*/  partitionReferenceNum; scalar_t__ logicalBlockNum; } ;
struct TYPE_10__ {int /*<<< orphan*/ * a_ops; } ;
struct inode {int i_size; int /*<<< orphan*/ * i_op; TYPE_1__ i_data; struct super_block* i_sb; } ;
struct extent_position {TYPE_4__* bh; int /*<<< orphan*/  offset; TYPE_2__ block; } ;
struct dentry {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/ * b_data; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFLNK ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  UDF_NAME_LEN_CS0 ; 
 int /*<<< orphan*/  brelse (TYPE_4__*) ; 
 int /*<<< orphan*/  discard_new_inode (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  inode_nohighmem (struct inode*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (TYPE_4__*) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (TYPE_4__*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  set_buffer_uptodate (TYPE_4__*) ; 
 int /*<<< orphan*/  udf_add_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,int,int /*<<< orphan*/ ) ; 
 int udf_add_nondir (struct dentry*,struct inode*) ; 
 int udf_ext0_offset (struct inode*) ; 
 int /*<<< orphan*/  udf_file_entry_alloc_offset (struct inode*) ; 
 scalar_t__ udf_get_pblock (struct super_block*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ udf_new_block (struct super_block*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct inode* udf_new_inode (struct inode*,int) ; 
 int udf_put_filename (struct super_block*,char const*,int,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_symlink_aops ; 
 int /*<<< orphan*/  udf_symlink_inode_operations ; 
 TYPE_4__* udf_tgetblk (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  udf_truncate_tail_extent (struct inode*) ; 
 int /*<<< orphan*/  unlock_buffer (TYPE_4__*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int udf_symlink(struct inode *dir, struct dentry *dentry,
		       const char *symname)
{
	struct inode *inode = udf_new_inode(dir, S_IFLNK | 0777);
	struct pathComponent *pc;
	const char *compstart;
	struct extent_position epos = {};
	int eoffset, elen = 0;
	uint8_t *ea;
	int err;
	udf_pblk_t block;
	unsigned char *name = NULL;
	int namelen;
	struct udf_inode_info *iinfo;
	struct super_block *sb = dir->i_sb;

	if (IS_ERR(inode))
		return PTR_ERR(inode);

	iinfo = UDF_I(inode);
	down_write(&iinfo->i_data_sem);
	name = kmalloc(UDF_NAME_LEN_CS0, GFP_NOFS);
	if (!name) {
		err = -ENOMEM;
		goto out_no_entry;
	}

	inode->i_data.a_ops = &udf_symlink_aops;
	inode->i_op = &udf_symlink_inode_operations;
	inode_nohighmem(inode);

	if (iinfo->i_alloc_type != ICBTAG_FLAG_AD_IN_ICB) {
		struct kernel_lb_addr eloc;
		uint32_t bsize;

		block = udf_new_block(sb, inode,
				iinfo->i_location.partitionReferenceNum,
				iinfo->i_location.logicalBlockNum, &err);
		if (!block)
			goto out_no_entry;
		epos.block = iinfo->i_location;
		epos.offset = udf_file_entry_alloc_offset(inode);
		epos.bh = NULL;
		eloc.logicalBlockNum = block;
		eloc.partitionReferenceNum =
				iinfo->i_location.partitionReferenceNum;
		bsize = sb->s_blocksize;
		iinfo->i_lenExtents = bsize;
		udf_add_aext(inode, &epos, &eloc, bsize, 0);
		brelse(epos.bh);

		block = udf_get_pblock(sb, block,
				iinfo->i_location.partitionReferenceNum,
				0);
		epos.bh = udf_tgetblk(sb, block);
		lock_buffer(epos.bh);
		memset(epos.bh->b_data, 0x00, bsize);
		set_buffer_uptodate(epos.bh);
		unlock_buffer(epos.bh);
		mark_buffer_dirty_inode(epos.bh, inode);
		ea = epos.bh->b_data + udf_ext0_offset(inode);
	} else
		ea = iinfo->i_ext.i_data + iinfo->i_lenEAttr;

	eoffset = sb->s_blocksize - udf_ext0_offset(inode);
	pc = (struct pathComponent *)ea;

	if (*symname == '/') {
		do {
			symname++;
		} while (*symname == '/');

		pc->componentType = 1;
		pc->lengthComponentIdent = 0;
		pc->componentFileVersionNum = 0;
		elen += sizeof(struct pathComponent);
	}

	err = -ENAMETOOLONG;

	while (*symname) {
		if (elen + sizeof(struct pathComponent) > eoffset)
			goto out_no_entry;

		pc = (struct pathComponent *)(ea + elen);

		compstart = symname;

		do {
			symname++;
		} while (*symname && *symname != '/');

		pc->componentType = 5;
		pc->lengthComponentIdent = 0;
		pc->componentFileVersionNum = 0;
		if (compstart[0] == '.') {
			if ((symname - compstart) == 1)
				pc->componentType = 4;
			else if ((symname - compstart) == 2 &&
					compstart[1] == '.')
				pc->componentType = 3;
		}

		if (pc->componentType == 5) {
			namelen = udf_put_filename(sb, compstart,
						   symname - compstart,
						   name, UDF_NAME_LEN_CS0);
			if (!namelen)
				goto out_no_entry;

			if (elen + sizeof(struct pathComponent) + namelen >
					eoffset)
				goto out_no_entry;
			else
				pc->lengthComponentIdent = namelen;

			memcpy(pc->componentIdent, name, namelen);
		}

		elen += sizeof(struct pathComponent) + pc->lengthComponentIdent;

		if (*symname) {
			do {
				symname++;
			} while (*symname == '/');
		}
	}

	brelse(epos.bh);
	inode->i_size = elen;
	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		iinfo->i_lenAlloc = inode->i_size;
	else
		udf_truncate_tail_extent(inode);
	mark_inode_dirty(inode);
	up_write(&iinfo->i_data_sem);

	err = udf_add_nondir(dentry, inode);
out:
	kfree(name);
	return err;

out_no_entry:
	up_write(&iinfo->i_data_sem);
	inode_dec_link_count(inode);
	discard_new_inode(inode);
	goto out;
}