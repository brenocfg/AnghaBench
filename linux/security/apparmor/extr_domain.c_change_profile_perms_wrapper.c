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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;
struct aa_profile {TYPE_1__ file; } ;
struct aa_perms {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int aa_audit_file (struct aa_profile*,struct aa_perms*,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,struct aa_label*,int /*<<< orphan*/ ,char const*,int) ; 
 int change_profile_perms (struct aa_profile*,struct aa_label*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aa_perms*) ; 

__attribute__((used)) static int change_profile_perms_wrapper(const char *op, const char *name,
					struct aa_profile *profile,
					struct aa_label *target, bool stack,
					u32 request, struct aa_perms *perms)
{
	const char *info = NULL;
	int error = 0;

	if (!error)
		error = change_profile_perms(profile, target, stack, request,
					     profile->file.start, perms);
	if (error)
		error = aa_audit_file(profile, perms, op, request, name,
				      NULL, target, GLOBAL_ROOT_UID, info,
				      error);

	return error;
}