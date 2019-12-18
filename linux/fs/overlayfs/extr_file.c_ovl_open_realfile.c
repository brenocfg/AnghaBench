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
struct file {int f_flags; int /*<<< orphan*/  f_path; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int FMODE_NONOTIFY ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int O_NOATIME ; 
 int /*<<< orphan*/  current_cred () ; 
 struct inode* file_inode (struct file const*) ; 
 struct file* open_with_fake_path (int /*<<< orphan*/ *,int,struct inode*,int /*<<< orphan*/ ) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_whatisit (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct file const*,struct file const*,int /*<<< orphan*/ ,int,struct file*,int) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 

__attribute__((used)) static struct file *ovl_open_realfile(const struct file *file,
				      struct inode *realinode)
{
	struct inode *inode = file_inode(file);
	struct file *realfile;
	const struct cred *old_cred;
	int flags = file->f_flags | O_NOATIME | FMODE_NONOTIFY;

	old_cred = ovl_override_creds(inode->i_sb);
	realfile = open_with_fake_path(&file->f_path, flags, realinode,
				       current_cred());
	revert_creds(old_cred);

	pr_debug("open(%p[%pD2/%c], 0%o) -> (%p, 0%o)\n",
		 file, file, ovl_whatisit(inode, realinode), file->f_flags,
		 realfile, IS_ERR(realfile) ? 0 : realfile->f_flags);

	return realfile;
}