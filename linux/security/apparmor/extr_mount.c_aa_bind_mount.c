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
 int EINVAL ; 
 int LOOKUP_AUTOMOUNT ; 
 int LOOKUP_FOLLOW ; 
 unsigned long MS_BIND ; 
 unsigned long MS_REC ; 
 int fn_for_each_confined (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_buffers (char*,char*) ; 
 int kern_path (char const*,int,struct path*) ; 
 int /*<<< orphan*/  match_mnt (struct aa_profile*,struct path const*,char*,struct path*,char*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  put_buffers (char*,char*) ; 

int aa_bind_mount(struct aa_label *label, const struct path *path,
		  const char *dev_name, unsigned long flags)
{
	struct aa_profile *profile;
	char *buffer = NULL, *old_buffer = NULL;
	struct path old_path;
	int error;

	AA_BUG(!label);
	AA_BUG(!path);

	if (!dev_name || !*dev_name)
		return -EINVAL;

	flags &= MS_REC | MS_BIND;

	error = kern_path(dev_name, LOOKUP_FOLLOW|LOOKUP_AUTOMOUNT, &old_path);
	if (error)
		return error;

	get_buffers(buffer, old_buffer);
	error = fn_for_each_confined(label, profile,
			match_mnt(profile, path, buffer, &old_path, old_buffer,
				  NULL, flags, NULL, false));
	put_buffers(buffer, old_buffer);
	path_put(&old_path);

	return error;
}