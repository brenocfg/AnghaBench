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
struct aa_profile {int /*<<< orphan*/  parent; TYPE_1__* ns; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct aa_profile* aa_get_newest_profile (struct aa_profile*) ; 
 int /*<<< orphan*/  aa_put_profile (struct aa_profile*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct aa_profile*) ; 
 struct aa_profile* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct aa_profile *update_to_newest_parent(struct aa_profile *new)
{
	struct aa_profile *parent, *newest;

	parent = rcu_dereference_protected(new->parent,
					   mutex_is_locked(&new->ns->lock));
	newest = aa_get_newest_profile(parent);

	/* parent replaced in this atomic set? */
	if (newest != parent) {
		aa_put_profile(parent);
		rcu_assign_pointer(new->parent, newest);
	} else
		aa_put_profile(newest);

	return newest;
}