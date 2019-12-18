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
struct common_audit_data {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  denied; int /*<<< orphan*/  allow; } ;
struct aa_profile {TYPE_1__ caps; } ;
struct TYPE_4__ {char* info; } ;

/* Variables and functions */
 unsigned int CAP_OPT_NOAUDIT ; 
 int /*<<< orphan*/  COMPLAIN_MODE (struct aa_profile*) ; 
 int EPERM ; 
 TYPE_2__* aad (struct common_audit_data*) ; 
 int audit_caps (struct common_audit_data*,struct aa_profile*,int,int) ; 
 scalar_t__ cap_raised (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int profile_capable(struct aa_profile *profile, int cap,
			   unsigned int opts, struct common_audit_data *sa)
{
	int error;

	if (cap_raised(profile->caps.allow, cap) &&
	    !cap_raised(profile->caps.denied, cap))
		error = 0;
	else
		error = -EPERM;

	if (opts & CAP_OPT_NOAUDIT) {
		if (!COMPLAIN_MODE(profile))
			return error;
		/* audit the cap request in complain mode but note that it
		 * should be optional.
		 */
		aad(sa)->info = "optional: no audit";
	}

	return audit_caps(sa, profile, cap, error);
}