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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct file {int f_mode; } ;

/* Variables and functions */
 int EPERM ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  IS_VERITY (struct inode*) ; 
 int ensure_verity_info (struct inode*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

int fsverity_file_open(struct inode *inode, struct file *filp)
{
	if (!IS_VERITY(inode))
		return 0;

	if (filp->f_mode & FMODE_WRITE) {
		pr_debug("Denying opening verity file (ino %lu) for write\n",
			 inode->i_ino);
		return -EPERM;
	}

	return ensure_verity_info(inode);
}