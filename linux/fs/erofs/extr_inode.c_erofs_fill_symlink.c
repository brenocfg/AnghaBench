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
struct inode {unsigned int i_size; char* i_link; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_sb; } ;
struct erofs_inode {scalar_t__ datalayout; int /*<<< orphan*/  nid; scalar_t__ xattr_isize; scalar_t__ inode_isize; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 int EFSCORRUPTED ; 
 int ENOMEM ; 
 struct erofs_inode* EROFS_I (struct inode*) ; 
 scalar_t__ EROFS_INODE_FLAT_INLINE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  erofs_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  erofs_fast_symlink_iops ; 
 int /*<<< orphan*/  erofs_symlink_iops ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,void*,unsigned int) ; 

__attribute__((used)) static int erofs_fill_symlink(struct inode *inode, void *data,
			      unsigned int m_pofs)
{
	struct erofs_inode *vi = EROFS_I(inode);
	char *lnk;

	/* if it cannot be handled with fast symlink scheme */
	if (vi->datalayout != EROFS_INODE_FLAT_INLINE ||
	    inode->i_size >= PAGE_SIZE) {
		inode->i_op = &erofs_symlink_iops;
		return 0;
	}

	lnk = kmalloc(inode->i_size + 1, GFP_KERNEL);
	if (!lnk)
		return -ENOMEM;

	m_pofs += vi->inode_isize + vi->xattr_isize;
	/* inline symlink data shouldn't cross page boundary as well */
	if (m_pofs + inode->i_size > PAGE_SIZE) {
		kfree(lnk);
		erofs_err(inode->i_sb,
			  "inline data cross block boundary @ nid %llu",
			  vi->nid);
		DBG_BUGON(1);
		return -EFSCORRUPTED;
	}

	memcpy(lnk, data + m_pofs, inode->i_size);
	lnk[inode->i_size] = '\0';

	inode->i_link = lnk;
	inode->i_op = &erofs_fast_symlink_iops;
	return 0;
}