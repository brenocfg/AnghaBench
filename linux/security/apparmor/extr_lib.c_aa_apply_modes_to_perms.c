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
struct aa_profile {int dummy; } ;
struct aa_perms {void* complain; void* kill; void* quiet; void* audit; } ;

/* Variables and functions */
 void* ALL_PERMS_MASK ; 
#define  AUDIT_ALL 131 
 int AUDIT_MODE (struct aa_profile*) ; 
#define  AUDIT_NOQUIET 130 
#define  AUDIT_QUIET 129 
#define  AUDIT_QUIET_DENIED 128 
 scalar_t__ COMPLAIN_MODE (struct aa_profile*) ; 
 scalar_t__ KILL_MODE (struct aa_profile*) ; 

void aa_apply_modes_to_perms(struct aa_profile *profile, struct aa_perms *perms)
{
	switch (AUDIT_MODE(profile)) {
	case AUDIT_ALL:
		perms->audit = ALL_PERMS_MASK;
		/* fall through */
	case AUDIT_NOQUIET:
		perms->quiet = 0;
		break;
	case AUDIT_QUIET:
		perms->audit = 0;
		/* fall through */
	case AUDIT_QUIET_DENIED:
		perms->quiet = ALL_PERMS_MASK;
		break;
	}

	if (KILL_MODE(profile))
		perms->kill = ALL_PERMS_MASK;
	else if (COMPLAIN_MODE(profile))
		perms->complain = ALL_PERMS_MASK;
/*
 *  TODO:
 *	else if (PROMPT_MODE(profile))
 *		perms->prompt = ALL_PERMS_MASK;
 */
}