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
struct path {int dummy; } ;
struct TYPE_2__ {unsigned int start; int /*<<< orphan*/  dfa; } ;
struct aa_profile {TYPE_1__ file; int /*<<< orphan*/  path_flags; int /*<<< orphan*/  label; } ;
struct aa_perms {int allow; int /*<<< orphan*/  xindex; int /*<<< orphan*/  kill; int /*<<< orphan*/  quiet; int /*<<< orphan*/  audit; } ;

/* Variables and functions */
 int AA_AUDIT_FILE_MASK ; 
 int AA_LINK_SUBSET ; 
 int AA_MAY_LINK ; 
 int EACCES ; 
 int MAY_EXEC ; 
 int /*<<< orphan*/  OP_LINK ; 
 int aa_audit_file (struct aa_profile*,struct aa_perms*,int /*<<< orphan*/ ,int,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 unsigned int aa_dfa_null_transition (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int aa_str_perms (int /*<<< orphan*/ ,unsigned int,char const*,struct path_cond*,struct aa_perms*) ; 
 int path_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct path const*,int /*<<< orphan*/ ,char*,char const**,struct path_cond*,int) ; 
 int /*<<< orphan*/  xindex_is_subset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int profile_path_link(struct aa_profile *profile,
			     const struct path *link, char *buffer,
			     const struct path *target, char *buffer2,
			     struct path_cond *cond)
{
	const char *lname, *tname = NULL;
	struct aa_perms lperms = {}, perms;
	const char *info = NULL;
	u32 request = AA_MAY_LINK;
	unsigned int state;
	int error;

	error = path_name(OP_LINK, &profile->label, link, profile->path_flags,
			  buffer, &lname, cond, AA_MAY_LINK);
	if (error)
		goto audit;

	/* buffer2 freed below, tname is pointer in buffer2 */
	error = path_name(OP_LINK, &profile->label, target, profile->path_flags,
			  buffer2, &tname, cond, AA_MAY_LINK);
	if (error)
		goto audit;

	error = -EACCES;
	/* aa_str_perms - handles the case of the dfa being NULL */
	state = aa_str_perms(profile->file.dfa, profile->file.start, lname,
			     cond, &lperms);

	if (!(lperms.allow & AA_MAY_LINK))
		goto audit;

	/* test to see if target can be paired with link */
	state = aa_dfa_null_transition(profile->file.dfa, state);
	aa_str_perms(profile->file.dfa, state, tname, cond, &perms);

	/* force audit/quiet masks for link are stored in the second entry
	 * in the link pair.
	 */
	lperms.audit = perms.audit;
	lperms.quiet = perms.quiet;
	lperms.kill = perms.kill;

	if (!(perms.allow & AA_MAY_LINK)) {
		info = "target restricted";
		lperms = perms;
		goto audit;
	}

	/* done if link subset test is not required */
	if (!(perms.allow & AA_LINK_SUBSET))
		goto done_tests;

	/* Do link perm subset test requiring allowed permission on link are
	 * a subset of the allowed permissions on target.
	 */
	aa_str_perms(profile->file.dfa, profile->file.start, tname, cond,
		     &perms);

	/* AA_MAY_LINK is not considered in the subset test */
	request = lperms.allow & ~AA_MAY_LINK;
	lperms.allow &= perms.allow | AA_MAY_LINK;

	request |= AA_AUDIT_FILE_MASK & (lperms.allow & ~perms.allow);
	if (request & ~lperms.allow) {
		goto audit;
	} else if ((lperms.allow & MAY_EXEC) &&
		   !xindex_is_subset(lperms.xindex, perms.xindex)) {
		lperms.allow &= ~MAY_EXEC;
		request |= MAY_EXEC;
		info = "link not subset of target";
		goto audit;
	}

done_tests:
	error = 0;

audit:
	return aa_audit_file(profile, &lperms, OP_LINK, request, lname, tname,
			     NULL, cond->uid, info, error);
}