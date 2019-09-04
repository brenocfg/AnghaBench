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
struct file {int dummy; } ;
struct autofs_sb_info {int dummy; } ;

/* Variables and functions */
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 

__attribute__((used)) static struct autofs_sb_info *autofs_dev_ioctl_sbi(struct file *f)
{
	struct autofs_sb_info *sbi = NULL;
	struct inode *inode;

	if (f) {
		inode = file_inode(f);
		sbi = autofs_sbi(inode->i_sb);
	}
	return sbi;
}