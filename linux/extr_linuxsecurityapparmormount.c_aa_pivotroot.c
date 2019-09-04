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
struct aa_profile {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  AA_MAY_PIVOTROOT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IS_ERR (struct aa_label*) ; 
 int /*<<< orphan*/  OP_PIVOTROOT ; 
 int PTR_ERR (struct aa_label*) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 int aa_replace_current_label (struct aa_label*) ; 
 int /*<<< orphan*/  audit_mount (struct aa_profile*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  build_pivotroot (struct aa_profile*,struct path const*,char*,struct path const*,char*) ; 
 int fn_for_each (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ) ; 
 struct aa_label* fn_label_build (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_buffers (char*,char*) ; 
 int /*<<< orphan*/  nullperms ; 
 int /*<<< orphan*/  put_buffers (char*,char*) ; 

int aa_pivotroot(struct aa_label *label, const struct path *old_path,
		 const struct path *new_path)
{
	struct aa_profile *profile;
	struct aa_label *target = NULL;
	char *old_buffer = NULL, *new_buffer = NULL, *info = NULL;
	int error;

	AA_BUG(!label);
	AA_BUG(!old_path);
	AA_BUG(!new_path);

	get_buffers(old_buffer, new_buffer);
	target = fn_label_build(label, profile, GFP_ATOMIC,
			build_pivotroot(profile, new_path, new_buffer,
					old_path, old_buffer));
	if (!target) {
		info = "label build failed";
		error = -ENOMEM;
		goto fail;
	} else if (!IS_ERR(target)) {
		error = aa_replace_current_label(target);
		if (error) {
			/* TODO: audit target */
			aa_put_label(target);
			goto out;
		}
	} else
		/* already audited error */
		error = PTR_ERR(target);
out:
	put_buffers(old_buffer, new_buffer);

	return error;

fail:
	/* TODO: add back in auditing of new_name and old_name */
	error = fn_for_each(label, profile,
			audit_mount(profile, OP_PIVOTROOT, NULL /*new_name */,
				    NULL /* old_name */,
				    NULL, NULL,
				    0, NULL, AA_MAY_PIVOTROOT, &nullperms, info,
				    error));
	goto out;
}