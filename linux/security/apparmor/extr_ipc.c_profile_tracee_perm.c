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
typedef  int /*<<< orphan*/  u32 ;
struct common_audit_data {int dummy; } ;
struct aa_profile {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_CLASS_PTRACE ; 
 int /*<<< orphan*/  PROFILE_MEDIATES (struct aa_profile*,int /*<<< orphan*/ ) ; 
 int profile_ptrace_perm (struct aa_profile*,struct aa_label*,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 scalar_t__ profile_unconfined (struct aa_profile*) ; 
 scalar_t__ unconfined (struct aa_label*) ; 

__attribute__((used)) static int profile_tracee_perm(struct aa_profile *tracee,
			       struct aa_label *tracer, u32 request,
			       struct common_audit_data *sa)
{
	if (profile_unconfined(tracee) || unconfined(tracer) ||
	    !PROFILE_MEDIATES(tracee, AA_CLASS_PTRACE))
		return 0;

	return profile_ptrace_perm(tracee, tracer, request, sa);
}