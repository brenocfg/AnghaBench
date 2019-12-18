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
typedef  int u32 ;
struct aa_profile {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_AUDIT_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_NONE ; 
 int /*<<< orphan*/  OP_PTRACE ; 
 int PTRACE_PERM_SHIFT ; 
 int /*<<< orphan*/  profile_tracee_perm (struct aa_profile*,struct aa_label*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  profile_tracer_perm (struct aa_profile*,struct aa_label*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa ; 
 int xcheck_labels (struct aa_label*,struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int aa_may_ptrace(struct aa_label *tracer, struct aa_label *tracee,
		  u32 request)
{
	struct aa_profile *profile;
	u32 xrequest = request << PTRACE_PERM_SHIFT;
	DEFINE_AUDIT_DATA(sa, LSM_AUDIT_DATA_NONE, OP_PTRACE);

	return xcheck_labels(tracer, tracee, profile,
			profile_tracer_perm(profile, tracee, request, &sa),
			profile_tracee_perm(profile, tracer, xrequest, &sa));
}