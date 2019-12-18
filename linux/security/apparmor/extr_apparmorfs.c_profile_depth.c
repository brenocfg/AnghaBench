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
struct aa_profile {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct aa_profile* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int profile_depth(struct aa_profile *profile)
{
	int depth = 0;

	rcu_read_lock();
	for (depth = 0; profile; profile = rcu_access_pointer(profile->parent))
		depth++;
	rcu_read_unlock();

	return depth;
}