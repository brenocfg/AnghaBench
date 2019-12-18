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
typedef  int u32 ;
struct path_cond {int /*<<< orphan*/  uid; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; int /*<<< orphan*/  dfa; } ;
struct aa_profile {TYPE_1__ file; } ;
struct aa_perms {int allow; } ;

/* Variables and functions */
 int EACCES ; 
 int aa_audit_file (struct aa_profile*,struct aa_perms*,char const*,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  aa_str_perms (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct path_cond*,struct aa_perms*) ; 
 scalar_t__ profile_unconfined (struct aa_profile*) ; 

int __aa_path_perm(const char *op, struct aa_profile *profile, const char *name,
		   u32 request, struct path_cond *cond, int flags,
		   struct aa_perms *perms)
{
	int e = 0;

	if (profile_unconfined(profile))
		return 0;
	aa_str_perms(profile->file.dfa, profile->file.start, name, cond, perms);
	if (request & ~perms->allow)
		e = -EACCES;
	return aa_audit_file(profile, perms, op, request, name, NULL, NULL,
			     cond->uid, NULL, e);
}