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
 unsigned long MS_PRIVATE ; 
 unsigned long MS_REC ; 
 unsigned long MS_SHARED ; 
 unsigned long MS_SILENT ; 
 unsigned long MS_SLAVE ; 
 unsigned long MS_UNBINDABLE ; 
 int fn_for_each_confined (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_buffers (char*) ; 
 int /*<<< orphan*/  match_mnt (struct aa_profile*,struct path const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_buffers (char*) ; 

int aa_mount_change_type(struct aa_label *label, const struct path *path,
			 unsigned long flags)
{
	struct aa_profile *profile;
	char *buffer = NULL;
	int error;

	AA_BUG(!label);
	AA_BUG(!path);

	/* These are the flags allowed by do_change_type() */
	flags &= (MS_REC | MS_SILENT | MS_SHARED | MS_PRIVATE | MS_SLAVE |
		  MS_UNBINDABLE);

	get_buffers(buffer);
	error = fn_for_each_confined(label, profile,
			match_mnt(profile, path, buffer, NULL, NULL, NULL,
				  flags, NULL, false));
	put_buffers(buffer);

	return error;
}