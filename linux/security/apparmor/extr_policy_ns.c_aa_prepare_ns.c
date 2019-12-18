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
struct aa_ns {int /*<<< orphan*/  lock; int /*<<< orphan*/  sub_ns; int /*<<< orphan*/  level; } ;

/* Variables and functions */
 struct aa_ns* __aa_create_ns (struct aa_ns*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __aa_find_ns (int /*<<< orphan*/ *,char const*) ; 
 struct aa_ns* aa_get_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct aa_ns *aa_prepare_ns(struct aa_ns *parent, const char *name)
{
	struct aa_ns *ns;

	mutex_lock_nested(&parent->lock, parent->level);
	/* try and find the specified ns and if it doesn't exist create it */
	/* released by caller */
	ns = aa_get_ns(__aa_find_ns(&parent->sub_ns, name));
	if (!ns)
		ns = __aa_create_ns(parent, name, NULL);
	mutex_unlock(&parent->lock);

	/* return ref */
	return ns;
}