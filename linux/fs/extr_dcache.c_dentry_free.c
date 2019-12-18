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
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct external_name {TYPE_2__ u; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_rcu; int /*<<< orphan*/  d_alias; } ;
struct dentry {int d_flags; TYPE_1__ d_u; } ;

/* Variables and functions */
 int DCACHE_NORCU ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __d_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __d_free_external (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  dname_external (struct dentry*) ; 
 struct external_name* external_name (struct dentry*) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dentry_free(struct dentry *dentry)
{
	WARN_ON(!hlist_unhashed(&dentry->d_u.d_alias));
	if (unlikely(dname_external(dentry))) {
		struct external_name *p = external_name(dentry);
		if (likely(atomic_dec_and_test(&p->u.count))) {
			call_rcu(&dentry->d_u.d_rcu, __d_free_external);
			return;
		}
	}
	/* if dentry was never visible to RCU, immediate free is OK */
	if (dentry->d_flags & DCACHE_NORCU)
		__d_free(&dentry->d_u.d_rcu);
	else
		call_rcu(&dentry->d_u.d_rcu, __d_free);
}