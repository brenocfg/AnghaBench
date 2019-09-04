#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct path_cond {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct path {struct dentry* dentry; int /*<<< orphan*/  mnt; } ;
struct dentry {int dummy; } ;
struct aa_profile {int dummy; } ;
struct aa_label {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 TYPE_1__* d_backing_inode (struct dentry*) ; 
 int fn_for_each_confined (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_buffers (char*,char*) ; 
 int /*<<< orphan*/  profile_path_link (struct aa_profile*,struct path*,char*,struct path*,char*,struct path_cond*) ; 
 int /*<<< orphan*/  put_buffers (char*,char*) ; 

int aa_path_link(struct aa_label *label, struct dentry *old_dentry,
		 const struct path *new_dir, struct dentry *new_dentry)
{
	struct path link = { .mnt = new_dir->mnt, .dentry = new_dentry };
	struct path target = { .mnt = new_dir->mnt, .dentry = old_dentry };
	struct path_cond cond = {
		d_backing_inode(old_dentry)->i_uid,
		d_backing_inode(old_dentry)->i_mode
	};
	char *buffer = NULL, *buffer2 = NULL;
	struct aa_profile *profile;
	int error;

	/* buffer freed below, lname is pointer in buffer */
	get_buffers(buffer, buffer2);
	error = fn_for_each_confined(label, profile,
			profile_path_link(profile, &link, buffer, &target,
					  buffer2, &cond));
	put_buffers(buffer, buffer2);

	return error;
}