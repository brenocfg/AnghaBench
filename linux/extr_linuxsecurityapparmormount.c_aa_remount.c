#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct path {TYPE_3__* dentry; } ;
struct aa_profile {int dummy; } ;
struct aa_label {int dummy; } ;
struct TYPE_6__ {TYPE_2__* d_sb; } ;
struct TYPE_5__ {TYPE_1__* s_type; } ;
struct TYPE_4__ {int fs_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int FS_BINARY_MOUNTDATA ; 
 int fn_for_each_confined (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_buffers (char*) ; 
 int /*<<< orphan*/  match_mnt (struct aa_profile*,struct path const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long,void*,int) ; 
 int /*<<< orphan*/  put_buffers (char*) ; 

int aa_remount(struct aa_label *label, const struct path *path,
	       unsigned long flags, void *data)
{
	struct aa_profile *profile;
	char *buffer = NULL;
	bool binary;
	int error;

	AA_BUG(!label);
	AA_BUG(!path);

	binary = path->dentry->d_sb->s_type->fs_flags & FS_BINARY_MOUNTDATA;

	get_buffers(buffer);
	error = fn_for_each_confined(label, profile,
			match_mnt(profile, path, buffer, NULL, NULL, NULL,
				  flags, data, binary));
	put_buffers(buffer);

	return error;
}