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
struct aa_profile {TYPE_1__* ns; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 struct aa_profile* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct aa_profile *aa_deref_parent(struct aa_profile *p)
{
	return rcu_dereference_protected(p->parent,
					 mutex_is_locked(&p->ns->lock));
}