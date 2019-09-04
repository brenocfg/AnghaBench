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
struct aa_ns {int /*<<< orphan*/  unconfined; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 struct aa_profile* __lookupn_profile (int /*<<< orphan*/ *,char const*,size_t) ; 
 struct aa_profile* aa_get_newest_profile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_get_profile_not0 (struct aa_profile*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 

struct aa_profile *aa_lookupn_profile(struct aa_ns *ns, const char *hname,
				      size_t n)
{
	struct aa_profile *profile;

	rcu_read_lock();
	do {
		profile = __lookupn_profile(&ns->base, hname, n);
	} while (profile && !aa_get_profile_not0(profile));
	rcu_read_unlock();

	/* the unconfined profile is not in the regular profile list */
	if (!profile && strncmp(hname, "unconfined", n) == 0)
		profile = aa_get_newest_profile(ns->unconfined);

	/* refcount released by caller */
	return profile;
}