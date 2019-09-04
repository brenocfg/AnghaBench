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
struct dentry {int dummy; } ;
struct aa_ns {int /*<<< orphan*/  sub_ns; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  EEXIST ; 
 struct aa_ns* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct aa_ns* __aa_create_ns (struct aa_ns*,char const*,struct dentry*) ; 
 int /*<<< orphan*/  __aa_find_ns (int /*<<< orphan*/ *,char const*) ; 
 struct aa_ns* aa_get_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

struct aa_ns *__aa_find_or_create_ns(struct aa_ns *parent, const char *name,
				     struct dentry *dir)
{
	struct aa_ns *ns;

	AA_BUG(!mutex_is_locked(&parent->lock));

	/* try and find the specified ns */
	/* released by caller */
	ns = aa_get_ns(__aa_find_ns(&parent->sub_ns, name));
	if (!ns)
		ns = __aa_create_ns(parent, name, dir);
	else
		ns = ERR_PTR(-EEXIST);

	/* return ref */
	return ns;
}