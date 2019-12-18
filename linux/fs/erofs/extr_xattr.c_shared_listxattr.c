#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_4__ {scalar_t__ blkaddr; int /*<<< orphan*/  page; int /*<<< orphan*/  kaddr; int /*<<< orphan*/  ofs; } ;
struct listxattr_iter {int buffer_ofs; TYPE_1__ it; int /*<<< orphan*/  dentry; } ;
struct inode {struct super_block* i_sb; } ;
struct erofs_sb_info {int dummy; } ;
struct erofs_inode {unsigned int xattr_shared_count; int /*<<< orphan*/ * xattr_shared_xattrs; } ;
typedef  scalar_t__ erofs_blk_t ;

/* Variables and functions */
 struct erofs_inode* EROFS_I (struct inode* const) ; 
 struct erofs_sb_info* EROFS_SB (struct super_block* const) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  erofs_get_meta_page (struct super_block* const,scalar_t__) ; 
 int /*<<< orphan*/  kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_xattr_handlers ; 
 int xattr_foreach (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xattr_iter_end (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xattr_iter_end_final (TYPE_1__*) ; 
 scalar_t__ xattrblock_addr (struct erofs_sb_info* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xattrblock_offset (struct erofs_sb_info* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int shared_listxattr(struct listxattr_iter *it)
{
	struct inode *const inode = d_inode(it->dentry);
	struct erofs_inode *const vi = EROFS_I(inode);
	struct super_block *const sb = inode->i_sb;
	struct erofs_sb_info *const sbi = EROFS_SB(sb);
	unsigned int i;
	int ret = 0;

	for (i = 0; i < vi->xattr_shared_count; ++i) {
		erofs_blk_t blkaddr =
			xattrblock_addr(sbi, vi->xattr_shared_xattrs[i]);

		it->it.ofs = xattrblock_offset(sbi, vi->xattr_shared_xattrs[i]);
		if (!i || blkaddr != it->it.blkaddr) {
			if (i)
				xattr_iter_end(&it->it, true);

			it->it.page = erofs_get_meta_page(sb, blkaddr);
			if (IS_ERR(it->it.page))
				return PTR_ERR(it->it.page);

			it->it.kaddr = kmap_atomic(it->it.page);
			it->it.blkaddr = blkaddr;
		}

		ret = xattr_foreach(&it->it, &list_xattr_handlers, NULL);
		if (ret)
			break;
	}
	if (vi->xattr_shared_count)
		xattr_iter_end_final(&it->it);

	return ret ? ret : it->buffer_ofs;
}