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
struct user_namespace {int dummy; } ;
struct ucounts {scalar_t__ count; int /*<<< orphan*/  node; int /*<<< orphan*/  uid; struct user_namespace* ns; } ;
struct hlist_head {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ INT_MAX ; 
 struct ucounts* find_ucounts (struct user_namespace*,int /*<<< orphan*/ ,struct hlist_head*) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 int /*<<< orphan*/  kfree (struct ucounts*) ; 
 struct ucounts* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct hlist_head* ucounts_hashentry (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucounts_lock ; 

__attribute__((used)) static struct ucounts *get_ucounts(struct user_namespace *ns, kuid_t uid)
{
	struct hlist_head *hashent = ucounts_hashentry(ns, uid);
	struct ucounts *ucounts, *new;

	spin_lock_irq(&ucounts_lock);
	ucounts = find_ucounts(ns, uid, hashent);
	if (!ucounts) {
		spin_unlock_irq(&ucounts_lock);

		new = kzalloc(sizeof(*new), GFP_KERNEL);
		if (!new)
			return NULL;

		new->ns = ns;
		new->uid = uid;
		new->count = 0;

		spin_lock_irq(&ucounts_lock);
		ucounts = find_ucounts(ns, uid, hashent);
		if (ucounts) {
			kfree(new);
		} else {
			hlist_add_head(&new->node, hashent);
			ucounts = new;
		}
	}
	if (ucounts->count == INT_MAX)
		ucounts = NULL;
	else
		ucounts->count += 1;
	spin_unlock_irq(&ucounts_lock);
	return ucounts;
}