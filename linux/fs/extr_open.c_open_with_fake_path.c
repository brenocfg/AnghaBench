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
struct path {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct path f_path; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 struct file* ERR_PTR (int) ; 
 int /*<<< orphan*/  IS_ERR (struct file*) ; 
 struct file* alloc_empty_file_noaccount (int,struct cred const*) ; 
 int do_dentry_open (struct file*,struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fput (struct file*) ; 

struct file *open_with_fake_path(const struct path *path, int flags,
				struct inode *inode, const struct cred *cred)
{
	struct file *f = alloc_empty_file_noaccount(flags, cred);
	if (!IS_ERR(f)) {
		int error;

		f->f_path = *path;
		error = do_dentry_open(f, inode, NULL);
		if (error) {
			fput(f);
			f = ERR_PTR(error);
		}
	}
	return f;
}