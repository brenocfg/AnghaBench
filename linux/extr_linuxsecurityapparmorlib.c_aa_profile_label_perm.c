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
struct common_audit_data {int dummy; } ;
struct aa_profile {int /*<<< orphan*/  label; } ;
struct aa_perms {int deny; } ;
struct TYPE_2__ {int request; int /*<<< orphan*/ * peer; int /*<<< orphan*/ * label; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_apply_modes_to_perms (struct aa_profile*,struct aa_perms*) ; 
 int /*<<< orphan*/  aa_audit_perms_cb ; 
 int aa_check_perms (struct aa_profile*,struct aa_perms*,int,struct common_audit_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_profile_match_label (struct aa_profile*,int /*<<< orphan*/ *,int,int,struct aa_perms*) ; 
 TYPE_1__* aad (struct common_audit_data*) ; 

int aa_profile_label_perm(struct aa_profile *profile, struct aa_profile *target,
			  u32 request, int type, u32 *deny,
			  struct common_audit_data *sa)
{
	struct aa_perms perms;

	aad(sa)->label = &profile->label;
	aad(sa)->peer = &target->label;
	aad(sa)->request = request;

	aa_profile_match_label(profile, &target->label, type, request, &perms);
	aa_apply_modes_to_perms(profile, &perms);
	*deny |= request & perms.deny;
	return aa_check_perms(profile, &perms, request, sa, aa_audit_perms_cb);
}