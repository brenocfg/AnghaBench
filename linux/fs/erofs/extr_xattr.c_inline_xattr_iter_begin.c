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
struct xattr_iter {int /*<<< orphan*/  page; int /*<<< orphan*/  kaddr; int /*<<< orphan*/  blkaddr; int /*<<< orphan*/  ofs; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct erofs_sb_info {int dummy; } ;
struct erofs_inode {unsigned int xattr_isize; unsigned int inode_isize; int /*<<< orphan*/  nid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 int ENOATTR ; 
 struct erofs_inode* EROFS_I (struct inode*) ; 
 struct erofs_sb_info* EROFS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  erofs_blknr (scalar_t__) ; 
 int /*<<< orphan*/  erofs_blkoff (scalar_t__) ; 
 int /*<<< orphan*/  erofs_get_meta_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iloc (struct erofs_sb_info* const,int /*<<< orphan*/ ) ; 
 unsigned int inlinexattr_header_size (struct inode*) ; 
 int /*<<< orphan*/  kmap_atomic (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inline_xattr_iter_begin(struct xattr_iter *it,
				   struct inode *inode)
{
	struct erofs_inode *const vi = EROFS_I(inode);
	struct erofs_sb_info *const sbi = EROFS_SB(inode->i_sb);
	unsigned int xattr_header_sz, inline_xattr_ofs;

	xattr_header_sz = inlinexattr_header_size(inode);
	if (xattr_header_sz >= vi->xattr_isize) {
		DBG_BUGON(xattr_header_sz > vi->xattr_isize);
		return -ENOATTR;
	}

	inline_xattr_ofs = vi->inode_isize + xattr_header_sz;

	it->blkaddr = erofs_blknr(iloc(sbi, vi->nid) + inline_xattr_ofs);
	it->ofs = erofs_blkoff(iloc(sbi, vi->nid) + inline_xattr_ofs);

	it->page = erofs_get_meta_page(inode->i_sb, it->blkaddr);
	if (IS_ERR(it->page))
		return PTR_ERR(it->page);

	it->kaddr = kmap_atomic(it->page);
	return vi->xattr_isize - xattr_header_sz;
}