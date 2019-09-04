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
struct aa_profile {int /*<<< orphan*/  disconnected; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  AA_CLASS_MOUNT ; 
 int EACCES ; 
 char* ERR_PTR (int) ; 
 int /*<<< orphan*/  PROFILE_MEDIATES (struct aa_profile*,int /*<<< orphan*/ ) ; 
 int aa_path_name (struct path*,int /*<<< orphan*/ ,char*,char const**,char const**,int /*<<< orphan*/ ) ; 
 int match_mnt_path_str (struct aa_profile*,struct path const*,char*,char const*,char const*,unsigned long,void*,int,char const*) ; 
 int /*<<< orphan*/  path_flags (struct aa_profile*,struct path*) ; 

__attribute__((used)) static int match_mnt(struct aa_profile *profile, const struct path *path,
		     char *buffer, struct path *devpath, char *devbuffer,
		     const char *type, unsigned long flags, void *data,
		     bool binary)
{
	const char *devname = NULL, *info = NULL;
	int error = -EACCES;

	AA_BUG(!profile);
	AA_BUG(devpath && !devbuffer);

	if (!PROFILE_MEDIATES(profile, AA_CLASS_MOUNT))
		return 0;

	if (devpath) {
		error = aa_path_name(devpath, path_flags(profile, devpath),
				     devbuffer, &devname, &info,
				     profile->disconnected);
		if (error)
			devname = ERR_PTR(error);
	}

	return match_mnt_path_str(profile, path, buffer, devname, type, flags,
				  data, binary, info);
}