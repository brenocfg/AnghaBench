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
struct vfsmount {int /*<<< orphan*/  mnt_root; } ;
struct path {int /*<<< orphan*/  dentry; struct vfsmount* mnt; } ;
struct aa_profile {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int fn_for_each_confined (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_buffers (char*) ; 
 int /*<<< orphan*/  profile_umount (struct aa_profile*,struct path*,char*) ; 
 int /*<<< orphan*/  put_buffers (char*) ; 

int aa_umount(struct aa_label *label, struct vfsmount *mnt, int flags)
{
	struct aa_profile *profile;
	char *buffer = NULL;
	int error;
	struct path path = { .mnt = mnt, .dentry = mnt->mnt_root };

	AA_BUG(!label);
	AA_BUG(!mnt);

	get_buffers(buffer);
	error = fn_for_each_confined(label, profile,
			profile_umount(profile, &path, buffer));
	put_buffers(buffer);

	return error;
}