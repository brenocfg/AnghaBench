#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct aa_label {int /*<<< orphan*/  flags; TYPE_1__* proxy; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  FLAG_STALE ; 
 int /*<<< orphan*/  aa_get_label (struct aa_label*) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 TYPE_3__* labels_ns (struct aa_label*) ; 
 TYPE_2__* labels_set (struct aa_label*) ; 
 int /*<<< orphan*/  lockdep_assert_held_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aa_label* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __aa_proxy_redirect(struct aa_label *orig, struct aa_label *new)
{
	struct aa_label *tmp;

	AA_BUG(!orig);
	AA_BUG(!new);
	lockdep_assert_held_write(&labels_set(orig)->lock);

	tmp = rcu_dereference_protected(orig->proxy->label,
					&labels_ns(orig)->lock);
	rcu_assign_pointer(orig->proxy->label, aa_get_label(new));
	orig->flags |= FLAG_STALE;
	aa_put_label(tmp);
}