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
struct aa_perms {int /*<<< orphan*/  xindex; int /*<<< orphan*/  quiet; int /*<<< orphan*/  audit; int /*<<< orphan*/  allow; } ;
struct aa_dfa {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dfa_user_allow (struct aa_dfa*,unsigned int) ; 
 int /*<<< orphan*/  dfa_user_audit (struct aa_dfa*,unsigned int) ; 
 int /*<<< orphan*/  dfa_user_quiet (struct aa_dfa*,unsigned int) ; 
 int /*<<< orphan*/  dfa_user_xindex (struct aa_dfa*,unsigned int) ; 

__attribute__((used)) static struct aa_perms compute_mnt_perms(struct aa_dfa *dfa,
					   unsigned int state)
{
	struct aa_perms perms = {
		.allow = dfa_user_allow(dfa, state),
		.audit = dfa_user_audit(dfa, state),
		.quiet = dfa_user_quiet(dfa, state),
		.xindex = dfa_user_xindex(dfa, state),
	};

	return perms;
}