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
struct aa_profile {int /*<<< orphan*/  ns; } ;
struct aa_ns {int dummy; } ;

/* Variables and functions */
 struct aa_profile* __first_profile (struct aa_ns*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __next_ns (struct aa_ns*,int /*<<< orphan*/ ) ; 
 struct aa_profile* __next_profile (struct aa_profile*) ; 

__attribute__((used)) static struct aa_profile *next_profile(struct aa_ns *root,
				       struct aa_profile *profile)
{
	struct aa_profile *next = __next_profile(profile);
	if (next)
		return next;

	/* finished all profiles in namespace move to next namespace */
	return __first_profile(root, __next_ns(root, profile->ns));
}