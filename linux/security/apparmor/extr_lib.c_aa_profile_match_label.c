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
struct TYPE_2__ {int /*<<< orphan*/ * start; int /*<<< orphan*/  dfa; } ;
struct aa_profile {TYPE_1__ policy; } ;
struct aa_perms {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 size_t AA_CLASS_LABEL ; 
 unsigned int aa_dfa_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aa_label_match (struct aa_profile*,struct aa_label*,unsigned int,int,int /*<<< orphan*/ ,struct aa_perms*) ; 

void aa_profile_match_label(struct aa_profile *profile, struct aa_label *label,
			    int type, u32 request, struct aa_perms *perms)
{
	/* TODO: doesn't yet handle extended types */
	unsigned int state;

	state = aa_dfa_next(profile->policy.dfa,
			    profile->policy.start[AA_CLASS_LABEL],
			    type);
	aa_label_match(profile, label, state, false, request, perms);
}