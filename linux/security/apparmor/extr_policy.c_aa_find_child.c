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
struct TYPE_2__ {int /*<<< orphan*/  profiles; } ;
struct aa_profile {TYPE_1__ base; } ;

/* Variables and functions */
 struct aa_profile* __find_child (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  aa_get_profile_not0 (struct aa_profile*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct aa_profile *aa_find_child(struct aa_profile *parent, const char *name)
{
	struct aa_profile *profile;

	rcu_read_lock();
	do {
		profile = __find_child(&parent->base.profiles, name);
	} while (profile && !aa_get_profile_not0(profile));
	rcu_read_unlock();

	/* refcount released by caller */
	return profile;
}