#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ udf_pblk_t ;
struct kernel_lb_addr {scalar_t__ logicalBlockNum; } ;
struct TYPE_11__ {int i_data; } ;
struct udf_inode_info {scalar_t__ i_alloc_type; int i_lenEAttr; int i_lenExtents; int i_lenAlloc; struct kernel_lb_addr i_location; TYPE_3__ i_ext; } ;
struct udf_fileident_bh {int soffset; int eoffset; TYPE_4__* sbh; TYPE_4__* ebh; } ;
struct tag {int dummy; } ;
struct super_block {int s_blocksize; int s_blocksize_bits; } ;
struct short_ad {int dummy; } ;
struct long_ad {int dummy; } ;
struct inode {int i_size; struct super_block* i_sb; } ;
struct TYPE_10__ {void* tagSerialNum; } ;
struct fileIdentDesc {int fileCharacteristics; int lengthFileIdent; void* lengthOfImpUse; void* fileVersionNum; TYPE_2__ descTag; } ;
struct extent_position {int offset; TYPE_4__* bh; struct kernel_lb_addr block; } ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
typedef  int sector_t ;
typedef  int loff_t ;
struct TYPE_13__ {int s_udfrev; } ;
struct TYPE_12__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int EXT_RECORDED_ALLOCATED ; 
 int FID_FILE_CHAR_DELETED ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 scalar_t__ ICBTAG_FLAG_AD_LONG ; 
 scalar_t__ ICBTAG_FLAG_AD_SHORT ; 
 int /*<<< orphan*/  TAG_IDENT_FID ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  UDF_NAME_LEN_CS0 ; 
 int /*<<< orphan*/  UDF_NAME_PAD ; 
 TYPE_8__* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (TYPE_4__*) ; 
 void* cpu_to_le16 (int) ; 
 int inode_bmap (struct inode*,int,struct extent_position*,struct kernel_lb_addr*,int*,int*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memset (struct fileIdentDesc*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* udf_bread (struct inode*,int,int,int*) ; 
 int /*<<< orphan*/  udf_current_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,int*,int) ; 
 int udf_dir_entry_len (struct fileIdentDesc*) ; 
 TYPE_4__* udf_expand_dir_adinicb (struct inode*,scalar_t__*,int*) ; 
 int udf_ext0_offset (struct inode*) ; 
 void* udf_file_entry_alloc_offset (struct inode*) ; 
 struct fileIdentDesc* udf_fileident_read (struct inode*,int*,struct udf_fileident_bh*,struct fileIdentDesc*,struct extent_position*,struct kernel_lb_addr*,int*,int*) ; 
 scalar_t__ udf_get_lb_pblock (struct super_block*,struct kernel_lb_addr*,int) ; 
 int /*<<< orphan*/  udf_new_tag (char*,int /*<<< orphan*/ ,int,int,scalar_t__,int) ; 
 int udf_next_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,int*,int) ; 
 int udf_put_filename (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* udf_tread (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  udf_write_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,int,int) ; 
 int /*<<< orphan*/  udf_write_fi (struct inode*,struct fileIdentDesc*,struct fileIdentDesc*,struct udf_fileident_bh*,int /*<<< orphan*/ *,unsigned char*) ; 

__attribute__((used)) static struct fileIdentDesc *udf_add_entry(struct inode *dir,
					   struct dentry *dentry,
					   struct udf_fileident_bh *fibh,
					   struct fileIdentDesc *cfi, int *err)
{
	struct super_block *sb = dir->i_sb;
	struct fileIdentDesc *fi = NULL;
	unsigned char *name = NULL;
	int namelen;
	loff_t f_pos;
	loff_t size = udf_ext0_offset(dir) + dir->i_size;
	int nfidlen;
	udf_pblk_t block;
	struct kernel_lb_addr eloc;
	uint32_t elen = 0;
	sector_t offset;
	struct extent_position epos = {};
	struct udf_inode_info *dinfo;

	fibh->sbh = fibh->ebh = NULL;
	name = kmalloc(UDF_NAME_LEN_CS0, GFP_NOFS);
	if (!name) {
		*err = -ENOMEM;
		goto out_err;
	}

	if (dentry) {
		if (!dentry->d_name.len) {
			*err = -EINVAL;
			goto out_err;
		}
		namelen = udf_put_filename(sb, dentry->d_name.name,
					   dentry->d_name.len,
					   name, UDF_NAME_LEN_CS0);
		if (!namelen) {
			*err = -ENAMETOOLONG;
			goto out_err;
		}
	} else {
		namelen = 0;
	}

	nfidlen = ALIGN(sizeof(struct fileIdentDesc) + namelen, UDF_NAME_PAD);

	f_pos = udf_ext0_offset(dir);

	fibh->soffset = fibh->eoffset = f_pos & (dir->i_sb->s_blocksize - 1);
	dinfo = UDF_I(dir);
	if (dinfo->i_alloc_type != ICBTAG_FLAG_AD_IN_ICB) {
		if (inode_bmap(dir, f_pos >> dir->i_sb->s_blocksize_bits, &epos,
		    &eloc, &elen, &offset) != (EXT_RECORDED_ALLOCATED >> 30)) {
			block = udf_get_lb_pblock(dir->i_sb,
					&dinfo->i_location, 0);
			fibh->soffset = fibh->eoffset = sb->s_blocksize;
			goto add;
		}
		block = udf_get_lb_pblock(dir->i_sb, &eloc, offset);
		if ((++offset << dir->i_sb->s_blocksize_bits) < elen) {
			if (dinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
				epos.offset -= sizeof(struct short_ad);
			else if (dinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
				epos.offset -= sizeof(struct long_ad);
		} else
			offset = 0;

		fibh->sbh = fibh->ebh = udf_tread(dir->i_sb, block);
		if (!fibh->sbh) {
			*err = -EIO;
			goto out_err;
		}

		block = dinfo->i_location.logicalBlockNum;
	}

	while (f_pos < size) {
		fi = udf_fileident_read(dir, &f_pos, fibh, cfi, &epos, &eloc,
					&elen, &offset);

		if (!fi) {
			*err = -EIO;
			goto out_err;
		}

		if ((cfi->fileCharacteristics & FID_FILE_CHAR_DELETED) != 0) {
			if (udf_dir_entry_len(cfi) == nfidlen) {
				cfi->descTag.tagSerialNum = cpu_to_le16(1);
				cfi->fileVersionNum = cpu_to_le16(1);
				cfi->fileCharacteristics = 0;
				cfi->lengthFileIdent = namelen;
				cfi->lengthOfImpUse = cpu_to_le16(0);
				if (!udf_write_fi(dir, cfi, fi, fibh, NULL,
						  name))
					goto out_ok;
				else {
					*err = -EIO;
					goto out_err;
				}
			}
		}
	}

add:
	f_pos += nfidlen;

	if (dinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB &&
	    sb->s_blocksize - fibh->eoffset < nfidlen) {
		brelse(epos.bh);
		epos.bh = NULL;
		fibh->soffset -= udf_ext0_offset(dir);
		fibh->eoffset -= udf_ext0_offset(dir);
		f_pos -= udf_ext0_offset(dir);
		if (fibh->sbh != fibh->ebh)
			brelse(fibh->ebh);
		brelse(fibh->sbh);
		fibh->sbh = fibh->ebh =
				udf_expand_dir_adinicb(dir, &block, err);
		if (!fibh->sbh)
			goto out_err;
		epos.block = dinfo->i_location;
		epos.offset = udf_file_entry_alloc_offset(dir);
		/* Load extent udf_expand_dir_adinicb() has created */
		udf_current_aext(dir, &epos, &eloc, &elen, 1);
	}

	/* Entry fits into current block? */
	if (sb->s_blocksize - fibh->eoffset >= nfidlen) {
		fibh->soffset = fibh->eoffset;
		fibh->eoffset += nfidlen;
		if (fibh->sbh != fibh->ebh) {
			brelse(fibh->sbh);
			fibh->sbh = fibh->ebh;
		}

		if (dinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) {
			block = dinfo->i_location.logicalBlockNum;
			fi = (struct fileIdentDesc *)
					(dinfo->i_ext.i_data +
					 fibh->soffset -
					 udf_ext0_offset(dir) +
					 dinfo->i_lenEAttr);
		} else {
			block = eloc.logicalBlockNum +
					((elen - 1) >>
						dir->i_sb->s_blocksize_bits);
			fi = (struct fileIdentDesc *)
				(fibh->sbh->b_data + fibh->soffset);
		}
	} else {
		/* Round up last extent in the file */
		elen = (elen + sb->s_blocksize - 1) & ~(sb->s_blocksize - 1);
		if (dinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
			epos.offset -= sizeof(struct short_ad);
		else if (dinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
			epos.offset -= sizeof(struct long_ad);
		udf_write_aext(dir, &epos, &eloc, elen, 1);
		dinfo->i_lenExtents = (dinfo->i_lenExtents + sb->s_blocksize
					- 1) & ~(sb->s_blocksize - 1);

		fibh->soffset = fibh->eoffset - sb->s_blocksize;
		fibh->eoffset += nfidlen - sb->s_blocksize;
		if (fibh->sbh != fibh->ebh) {
			brelse(fibh->sbh);
			fibh->sbh = fibh->ebh;
		}

		block = eloc.logicalBlockNum + ((elen - 1) >>
						dir->i_sb->s_blocksize_bits);
		fibh->ebh = udf_bread(dir,
				f_pos >> dir->i_sb->s_blocksize_bits, 1, err);
		if (!fibh->ebh)
			goto out_err;
		/* Extents could have been merged, invalidate our position */
		brelse(epos.bh);
		epos.bh = NULL;
		epos.block = dinfo->i_location;
		epos.offset = udf_file_entry_alloc_offset(dir);

		if (!fibh->soffset) {
			/* Find the freshly allocated block */
			while (udf_next_aext(dir, &epos, &eloc, &elen, 1) ==
				(EXT_RECORDED_ALLOCATED >> 30))
				;
			block = eloc.logicalBlockNum + ((elen - 1) >>
					dir->i_sb->s_blocksize_bits);
			brelse(fibh->sbh);
			fibh->sbh = fibh->ebh;
			fi = (struct fileIdentDesc *)(fibh->sbh->b_data);
		} else {
			fi = (struct fileIdentDesc *)
				(fibh->sbh->b_data + sb->s_blocksize +
					fibh->soffset);
		}
	}

	memset(cfi, 0, sizeof(struct fileIdentDesc));
	if (UDF_SB(sb)->s_udfrev >= 0x0200)
		udf_new_tag((char *)cfi, TAG_IDENT_FID, 3, 1, block,
			    sizeof(struct tag));
	else
		udf_new_tag((char *)cfi, TAG_IDENT_FID, 2, 1, block,
			    sizeof(struct tag));
	cfi->fileVersionNum = cpu_to_le16(1);
	cfi->lengthFileIdent = namelen;
	cfi->lengthOfImpUse = cpu_to_le16(0);
	if (!udf_write_fi(dir, cfi, fi, fibh, NULL, name)) {
		dir->i_size += nfidlen;
		if (dinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
			dinfo->i_lenAlloc += nfidlen;
		else {
			/* Find the last extent and truncate it to proper size */
			while (udf_next_aext(dir, &epos, &eloc, &elen, 1) ==
				(EXT_RECORDED_ALLOCATED >> 30))
				;
			elen -= dinfo->i_lenExtents - dir->i_size;
			if (dinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
				epos.offset -= sizeof(struct short_ad);
			else if (dinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
				epos.offset -= sizeof(struct long_ad);
			udf_write_aext(dir, &epos, &eloc, elen, 1);
			dinfo->i_lenExtents = dir->i_size;
		}

		mark_inode_dirty(dir);
		goto out_ok;
	} else {
		*err = -EIO;
		goto out_err;
	}

out_err:
	fi = NULL;
	if (fibh->sbh != fibh->ebh)
		brelse(fibh->ebh);
	brelse(fibh->sbh);
out_ok:
	brelse(epos.bh);
	kfree(name);
	return fi;
}