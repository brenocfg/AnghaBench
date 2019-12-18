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
typedef  scalar_t__ u32 ;
struct path_cond {int /*<<< orphan*/  mode; int /*<<< orphan*/  uid; } ;
struct file {int /*<<< orphan*/  f_path; } ;
struct aa_profile {int dummy; } ;
struct aa_perms {int dummy; } ;
struct aa_label {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 int PATH_DELEGATE_DELETED ; 
 int PATH_IS_DIR ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ aa_label_is_subset (struct aa_label*,struct aa_label*) ; 
 int /*<<< orphan*/  file_ctx (struct file*) ; 
 TYPE_1__* file_inode (struct file*) ; 
 int fn_for_each (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ) ; 
 int fn_for_each_not_in_set (struct aa_label*,struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_buffers (char*) ; 
 int /*<<< orphan*/  profile_path_perm (char const*,struct aa_profile*,int /*<<< orphan*/ *,char*,scalar_t__,struct path_cond*,int,struct aa_perms*) ; 
 int /*<<< orphan*/  put_buffers (char*) ; 
 int /*<<< orphan*/  update_file_ctx (int /*<<< orphan*/ ,struct aa_label*,scalar_t__) ; 

__attribute__((used)) static int __file_path_perm(const char *op, struct aa_label *label,
			    struct aa_label *flabel, struct file *file,
			    u32 request, u32 denied)
{
	struct aa_profile *profile;
	struct aa_perms perms = {};
	struct path_cond cond = {
		.uid = file_inode(file)->i_uid,
		.mode = file_inode(file)->i_mode
	};
	char *buffer;
	int flags, error;

	/* revalidation due to label out of date. No revocation at this time */
	if (!denied && aa_label_is_subset(flabel, label))
		/* TODO: check for revocation on stale profiles */
		return 0;

	flags = PATH_DELEGATE_DELETED | (S_ISDIR(cond.mode) ? PATH_IS_DIR : 0);
	get_buffers(buffer);

	/* check every profile in task label not in current cache */
	error = fn_for_each_not_in_set(flabel, label, profile,
			profile_path_perm(op, profile, &file->f_path, buffer,
					  request, &cond, flags, &perms));
	if (denied && !error) {
		/*
		 * check every profile in file label that was not tested
		 * in the initial check above.
		 *
		 * TODO: cache full perms so this only happens because of
		 * conditionals
		 * TODO: don't audit here
		 */
		if (label == flabel)
			error = fn_for_each(label, profile,
				profile_path_perm(op, profile, &file->f_path,
						  buffer, request, &cond, flags,
						  &perms));
		else
			error = fn_for_each_not_in_set(label, flabel, profile,
				profile_path_perm(op, profile, &file->f_path,
						  buffer, request, &cond, flags,
						  &perms));
	}
	if (!error)
		update_file_ctx(file_ctx(file), label, request);

	put_buffers(buffer);

	return error;
}