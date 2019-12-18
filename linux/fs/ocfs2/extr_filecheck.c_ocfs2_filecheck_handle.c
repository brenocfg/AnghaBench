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
struct ocfs2_super {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int OCFS2_FILECHECK_ERR_END ; 
 unsigned int OCFS2_FILECHECK_ERR_FAILED ; 
 int OCFS2_FILECHECK_ERR_START ; 
 unsigned int OCFS2_FILECHECK_ERR_SUCCESS ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* ocfs2_iget (struct ocfs2_super*,unsigned long,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
ocfs2_filecheck_handle(struct ocfs2_super *osb,
		       unsigned long ino, unsigned int flags)
{
	unsigned int ret = OCFS2_FILECHECK_ERR_SUCCESS;
	struct inode *inode = NULL;
	int rc;

	inode = ocfs2_iget(osb, ino, flags, 0);
	if (IS_ERR(inode)) {
		rc = (int)(-(long)inode);
		if (rc >= OCFS2_FILECHECK_ERR_START &&
		    rc < OCFS2_FILECHECK_ERR_END)
			ret = rc;
		else
			ret = OCFS2_FILECHECK_ERR_FAILED;
	} else
		iput(inode);

	return ret;
}