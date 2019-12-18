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
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int /*<<< orphan*/  TOMOYO_TYPE_CHGRP ; 
 int /*<<< orphan*/  TOMOYO_TYPE_CHOWN ; 
 int /*<<< orphan*/  from_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int tomoyo_path_number_perm (int /*<<< orphan*/ ,struct path const*,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tomoyo_path_chown(const struct path *path, kuid_t uid, kgid_t gid)
{
	int error = 0;

	if (uid_valid(uid))
		error = tomoyo_path_number_perm(TOMOYO_TYPE_CHOWN, path,
						from_kuid(&init_user_ns, uid));
	if (!error && gid_valid(gid))
		error = tomoyo_path_number_perm(TOMOYO_TYPE_CHGRP, path,
						from_kgid(&init_user_ns, gid));
	return error;
}