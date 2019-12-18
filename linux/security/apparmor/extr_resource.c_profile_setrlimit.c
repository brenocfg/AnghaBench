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
struct rlimit {scalar_t__ rlim_max; } ;
struct TYPE_4__ {int mask; TYPE_1__* limits; } ;
struct aa_profile {TYPE_2__ rlimits; } ;
struct TYPE_3__ {scalar_t__ rlim_max; } ;

/* Variables and functions */
 int EACCES ; 
 int audit_resource (struct aa_profile*,unsigned int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int profile_setrlimit(struct aa_profile *profile, unsigned int resource,
			     struct rlimit *new_rlim)
{
	int e = 0;

	if (profile->rlimits.mask & (1 << resource) && new_rlim->rlim_max >
	    profile->rlimits.limits[resource].rlim_max)
		e = -EACCES;
	return audit_resource(profile, resource, new_rlim->rlim_max, NULL, NULL,
			      e);
}