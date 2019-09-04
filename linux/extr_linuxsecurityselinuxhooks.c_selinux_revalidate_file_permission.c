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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {int f_flags; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int MAY_APPEND ; 
 int MAY_WRITE ; 
 int O_APPEND ; 
 struct cred* current_cred () ; 
 int file_has_perm (struct cred const*,struct file*,int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  file_mask_to_av (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int selinux_revalidate_file_permission(struct file *file, int mask)
{
	const struct cred *cred = current_cred();
	struct inode *inode = file_inode(file);

	/* file_mask_to_av won't add FILE__WRITE if MAY_APPEND is set */
	if ((file->f_flags & O_APPEND) && (mask & MAY_WRITE))
		mask |= MAY_APPEND;

	return file_has_perm(cred, file,
			     file_mask_to_av(inode->i_mode, mask));
}