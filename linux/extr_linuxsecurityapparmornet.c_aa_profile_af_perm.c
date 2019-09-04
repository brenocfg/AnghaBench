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
typedef  scalar_t__ u16 ;
struct common_audit_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dfa; } ;
struct aa_profile {TYPE_1__ policy; } ;
struct aa_perms {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  AA_CLASS_NET ; 
 scalar_t__ AF_MAX ; 
 unsigned int PROFILE_MEDIATES (struct aa_profile*,int /*<<< orphan*/ ) ; 
 int SOCK_MAX ; 
 int /*<<< orphan*/  aa_apply_modes_to_perms (struct aa_profile*,struct aa_perms*) ; 
 int aa_check_perms (struct aa_profile*,struct aa_perms*,int /*<<< orphan*/ ,struct common_audit_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_compute_perms (int /*<<< orphan*/ ,unsigned int,struct aa_perms*) ; 
 unsigned int aa_dfa_match_len (int /*<<< orphan*/ ,unsigned int,char*,int) ; 
 int /*<<< orphan*/  audit_net_cb ; 
 int /*<<< orphan*/  cpu_to_be16 (scalar_t__) ; 
 scalar_t__ profile_unconfined (struct aa_profile*) ; 

int aa_profile_af_perm(struct aa_profile *profile, struct common_audit_data *sa,
		       u32 request, u16 family, int type)
{
	struct aa_perms perms = { };
	unsigned int state;
	__be16 buffer[2];

	AA_BUG(family >= AF_MAX);
	AA_BUG(type < 0 || type >= SOCK_MAX);

	if (profile_unconfined(profile))
		return 0;
	state = PROFILE_MEDIATES(profile, AA_CLASS_NET);
	if (!state)
		return 0;

	buffer[0] = cpu_to_be16(family);
	buffer[1] = cpu_to_be16((u16) type);
	state = aa_dfa_match_len(profile->policy.dfa, state, (char *) &buffer,
				 4);
	aa_compute_perms(profile->policy.dfa, state, &perms);
	aa_apply_modes_to_perms(profile, &perms);

	return aa_check_perms(profile, &perms, request, sa, audit_net_cb);
}