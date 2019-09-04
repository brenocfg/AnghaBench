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
struct path {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dfa; int /*<<< orphan*/ * start; } ;
struct aa_profile {TYPE_1__ policy; int /*<<< orphan*/  disconnected; } ;
struct aa_perms {int allow; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 size_t AA_CLASS_MOUNT ; 
 int AA_MAY_UMOUNT ; 
 int EACCES ; 
 int /*<<< orphan*/  OP_UMOUNT ; 
 int /*<<< orphan*/  PROFILE_MEDIATES (struct aa_profile*,size_t) ; 
 unsigned int aa_dfa_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int aa_path_name (struct path*,int /*<<< orphan*/ ,char*,char const**,char const**,int /*<<< orphan*/ ) ; 
 int audit_mount (struct aa_profile*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct aa_perms*,char const*,int) ; 
 struct aa_perms compute_mnt_perms (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  path_flags (struct aa_profile*,struct path*) ; 

__attribute__((used)) static int profile_umount(struct aa_profile *profile, struct path *path,
			  char *buffer)
{
	struct aa_perms perms = { };
	const char *name = NULL, *info = NULL;
	unsigned int state;
	int error;

	AA_BUG(!profile);
	AA_BUG(!path);

	if (!PROFILE_MEDIATES(profile, AA_CLASS_MOUNT))
		return 0;

	error = aa_path_name(path, path_flags(profile, path), buffer, &name,
			     &info, profile->disconnected);
	if (error)
		goto audit;

	state = aa_dfa_match(profile->policy.dfa,
			     profile->policy.start[AA_CLASS_MOUNT],
			     name);
	perms = compute_mnt_perms(profile->policy.dfa, state);
	if (AA_MAY_UMOUNT & ~perms.allow)
		error = -EACCES;

audit:
	return audit_mount(profile, OP_UMOUNT, name, NULL, NULL, NULL, 0, NULL,
			   AA_MAY_UMOUNT, &perms, info, error);
}