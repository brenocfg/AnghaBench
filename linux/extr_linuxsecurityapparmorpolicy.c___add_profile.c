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
struct list_head {int dummy; } ;
struct aa_label {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;
struct aa_profile {struct aa_label label; TYPE_2__* ns; TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  labels; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  aa_get_profile (struct aa_profile*) ; 
 struct aa_label* aa_label_insert (int /*<<< orphan*/ *,struct aa_label*) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __add_profile(struct list_head *list, struct aa_profile *profile)
{
	struct aa_label *l;

	AA_BUG(!list);
	AA_BUG(!profile);
	AA_BUG(!profile->ns);
	AA_BUG(!mutex_is_locked(&profile->ns->lock));

	list_add_rcu(&profile->base.list, list);
	/* get list reference */
	aa_get_profile(profile);
	l = aa_label_insert(&profile->ns->labels, &profile->label);
	AA_BUG(l != &profile->label);
	aa_put_label(l);
}