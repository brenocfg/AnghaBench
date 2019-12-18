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
typedef  int /*<<< orphan*/  uint ;
struct xattr_iter {scalar_t__ ofs; scalar_t__ kaddr; void* page; int /*<<< orphan*/  blkaddr; } ;
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct erofs_xattr_ibody_header {unsigned int h_shared_count; } ;
struct erofs_sb_info {int dummy; } ;
struct erofs_inode {int xattr_isize; unsigned int xattr_shared_count; int /*<<< orphan*/  flags; int /*<<< orphan*/ * xattr_shared_xattrs; scalar_t__ inode_isize; int /*<<< orphan*/  nid; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 int EFSCORRUPTED ; 
 int ENOATTR ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int ERESTARTSYS ; 
 scalar_t__ EROFS_BLKSIZ ; 
 struct erofs_inode* EROFS_I (struct inode*) ; 
 int /*<<< orphan*/  EROFS_I_BL_XATTR_BIT ; 
 int /*<<< orphan*/  EROFS_I_EA_INITED_BIT ; 
 struct erofs_sb_info* EROFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  clear_and_wake_up_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  erofs_blknr (scalar_t__) ; 
 scalar_t__ erofs_blkoff (scalar_t__) ; 
 int /*<<< orphan*/  erofs_err (struct super_block*,char*,int,...) ; 
 void* erofs_get_meta_page (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ iloc (struct erofs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ kmap (void*) ; 
 scalar_t__ kmap_atomic (void*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ wait_on_bit_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xattr_iter_end (struct xattr_iter*,int) ; 

__attribute__((used)) static int init_inode_xattrs(struct inode *inode)
{
	struct erofs_inode *const vi = EROFS_I(inode);
	struct xattr_iter it;
	unsigned int i;
	struct erofs_xattr_ibody_header *ih;
	struct super_block *sb;
	struct erofs_sb_info *sbi;
	bool atomic_map;
	int ret = 0;

	/* the most case is that xattrs of this inode are initialized. */
	if (test_bit(EROFS_I_EA_INITED_BIT, &vi->flags))
		return 0;

	if (wait_on_bit_lock(&vi->flags, EROFS_I_BL_XATTR_BIT, TASK_KILLABLE))
		return -ERESTARTSYS;

	/* someone has initialized xattrs for us? */
	if (test_bit(EROFS_I_EA_INITED_BIT, &vi->flags))
		goto out_unlock;

	/*
	 * bypass all xattr operations if ->xattr_isize is not greater than
	 * sizeof(struct erofs_xattr_ibody_header), in detail:
	 * 1) it is not enough to contain erofs_xattr_ibody_header then
	 *    ->xattr_isize should be 0 (it means no xattr);
	 * 2) it is just to contain erofs_xattr_ibody_header, which is on-disk
	 *    undefined right now (maybe use later with some new sb feature).
	 */
	if (vi->xattr_isize == sizeof(struct erofs_xattr_ibody_header)) {
		erofs_err(inode->i_sb,
			  "xattr_isize %d of nid %llu is not supported yet",
			  vi->xattr_isize, vi->nid);
		ret = -EOPNOTSUPP;
		goto out_unlock;
	} else if (vi->xattr_isize < sizeof(struct erofs_xattr_ibody_header)) {
		if (vi->xattr_isize) {
			erofs_err(inode->i_sb,
				  "bogus xattr ibody @ nid %llu", vi->nid);
			DBG_BUGON(1);
			ret = -EFSCORRUPTED;
			goto out_unlock;	/* xattr ondisk layout error */
		}
		ret = -ENOATTR;
		goto out_unlock;
	}

	sb = inode->i_sb;
	sbi = EROFS_SB(sb);
	it.blkaddr = erofs_blknr(iloc(sbi, vi->nid) + vi->inode_isize);
	it.ofs = erofs_blkoff(iloc(sbi, vi->nid) + vi->inode_isize);

	it.page = erofs_get_meta_page(sb, it.blkaddr);
	if (IS_ERR(it.page)) {
		ret = PTR_ERR(it.page);
		goto out_unlock;
	}

	/* read in shared xattr array (non-atomic, see kmalloc below) */
	it.kaddr = kmap(it.page);
	atomic_map = false;

	ih = (struct erofs_xattr_ibody_header *)(it.kaddr + it.ofs);

	vi->xattr_shared_count = ih->h_shared_count;
	vi->xattr_shared_xattrs = kmalloc_array(vi->xattr_shared_count,
						sizeof(uint), GFP_KERNEL);
	if (!vi->xattr_shared_xattrs) {
		xattr_iter_end(&it, atomic_map);
		ret = -ENOMEM;
		goto out_unlock;
	}

	/* let's skip ibody header */
	it.ofs += sizeof(struct erofs_xattr_ibody_header);

	for (i = 0; i < vi->xattr_shared_count; ++i) {
		if (it.ofs >= EROFS_BLKSIZ) {
			/* cannot be unaligned */
			DBG_BUGON(it.ofs != EROFS_BLKSIZ);
			xattr_iter_end(&it, atomic_map);

			it.page = erofs_get_meta_page(sb, ++it.blkaddr);
			if (IS_ERR(it.page)) {
				kfree(vi->xattr_shared_xattrs);
				vi->xattr_shared_xattrs = NULL;
				ret = PTR_ERR(it.page);
				goto out_unlock;
			}

			it.kaddr = kmap_atomic(it.page);
			atomic_map = true;
			it.ofs = 0;
		}
		vi->xattr_shared_xattrs[i] =
			le32_to_cpu(*(__le32 *)(it.kaddr + it.ofs));
		it.ofs += sizeof(__le32);
	}
	xattr_iter_end(&it, atomic_map);

	set_bit(EROFS_I_EA_INITED_BIT, &vi->flags);

out_unlock:
	clear_and_wake_up_bit(EROFS_I_BL_XATTR_BIT, &vi->flags);
	return ret;
}