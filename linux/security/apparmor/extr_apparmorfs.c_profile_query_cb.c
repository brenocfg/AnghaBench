#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct path_cond {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * start; struct aa_dfa* dfa; } ;
struct TYPE_3__ {int /*<<< orphan*/  start; struct aa_dfa* dfa; } ;
struct aa_profile {TYPE_2__ policy; TYPE_1__ file; } ;
struct aa_perms {int dummy; } ;
struct aa_dfa {int dummy; } ;

/* Variables and functions */
 char const AA_CLASS_FILE ; 
 int /*<<< orphan*/  PROFILE_MEDIATES (struct aa_profile*,char const) ; 
 int /*<<< orphan*/  aa_apply_modes_to_perms (struct aa_profile*,struct aa_perms*) ; 
 struct aa_perms aa_compute_fperms (struct aa_dfa*,unsigned int,struct path_cond*) ; 
 int /*<<< orphan*/  aa_compute_perms (struct aa_dfa*,unsigned int,struct aa_perms*) ; 
 unsigned int aa_dfa_match_len (struct aa_dfa*,int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  aa_perms_accum_raw (struct aa_perms*,struct aa_perms*) ; 
 scalar_t__ profile_unconfined (struct aa_profile*) ; 

__attribute__((used)) static void profile_query_cb(struct aa_profile *profile, struct aa_perms *perms,
			     const char *match_str, size_t match_len)
{
	struct aa_perms tmp = { };
	struct aa_dfa *dfa;
	unsigned int state = 0;

	if (profile_unconfined(profile))
		return;
	if (profile->file.dfa && *match_str == AA_CLASS_FILE) {
		dfa = profile->file.dfa;
		state = aa_dfa_match_len(dfa, profile->file.start,
					 match_str + 1, match_len - 1);
		if (state) {
			struct path_cond cond = { };

			tmp = aa_compute_fperms(dfa, state, &cond);
		}
	} else if (profile->policy.dfa) {
		if (!PROFILE_MEDIATES(profile, *match_str))
			return;	/* no change to current perms */
		dfa = profile->policy.dfa;
		state = aa_dfa_match_len(dfa, profile->policy.start[0],
					 match_str, match_len);
		if (state)
			aa_compute_perms(dfa, state, &tmp);
	}
	aa_apply_modes_to_perms(profile, &tmp);
	aa_perms_accum_raw(perms, &tmp);
}