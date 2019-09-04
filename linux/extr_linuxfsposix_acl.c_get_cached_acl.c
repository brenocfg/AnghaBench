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
struct posix_acl {int /*<<< orphan*/  a_refcount; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct posix_acl** acl_by_type (struct inode*,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ is_uncached_acl (struct posix_acl*) ; 
 struct posix_acl* rcu_dereference (struct posix_acl*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ refcount_inc_not_zero (int /*<<< orphan*/ *) ; 

struct posix_acl *get_cached_acl(struct inode *inode, int type)
{
	struct posix_acl **p = acl_by_type(inode, type);
	struct posix_acl *acl;

	for (;;) {
		rcu_read_lock();
		acl = rcu_dereference(*p);
		if (!acl || is_uncached_acl(acl) ||
		    refcount_inc_not_zero(&acl->a_refcount))
			break;
		rcu_read_unlock();
		cpu_relax();
	}
	rcu_read_unlock();
	return acl;
}