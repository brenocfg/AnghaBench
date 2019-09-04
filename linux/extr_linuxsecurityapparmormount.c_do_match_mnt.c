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
struct aa_perms {int allow; } ;
struct aa_dfa {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int AA_MAY_MOUNT ; 
 int AA_MNT_CONT_MATCH ; 
 unsigned int aa_dfa_match (struct aa_dfa*,unsigned int,void*) ; 
 unsigned int aa_dfa_null_transition (struct aa_dfa*,unsigned int) ; 
 struct aa_perms compute_mnt_perms (struct aa_dfa*,unsigned int) ; 
 unsigned int match_mnt_flags (struct aa_dfa*,unsigned int,unsigned long) ; 

__attribute__((used)) static int do_match_mnt(struct aa_dfa *dfa, unsigned int start,
			const char *mntpnt, const char *devname,
			const char *type, unsigned long flags,
			void *data, bool binary, struct aa_perms *perms)
{
	unsigned int state;

	AA_BUG(!dfa);
	AA_BUG(!perms);

	state = aa_dfa_match(dfa, start, mntpnt);
	state = aa_dfa_null_transition(dfa, state);
	if (!state)
		return 1;

	if (devname)
		state = aa_dfa_match(dfa, state, devname);
	state = aa_dfa_null_transition(dfa, state);
	if (!state)
		return 2;

	if (type)
		state = aa_dfa_match(dfa, state, type);
	state = aa_dfa_null_transition(dfa, state);
	if (!state)
		return 3;

	state = match_mnt_flags(dfa, state, flags);
	if (!state)
		return 4;
	*perms = compute_mnt_perms(dfa, state);
	if (perms->allow & AA_MAY_MOUNT)
		return 0;

	/* only match data if not binary and the DFA flags data is expected */
	if (data && !binary && (perms->allow & AA_MNT_CONT_MATCH)) {
		state = aa_dfa_null_transition(dfa, state);
		if (!state)
			return 4;

		state = aa_dfa_match(dfa, state, data);
		if (!state)
			return 5;
		*perms = compute_mnt_perms(dfa, state);
		if (perms->allow & AA_MAY_MOUNT)
			return 0;
	}

	/* failed at end of flags match */
	return 4;
}