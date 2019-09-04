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
struct pid_namespace {int /*<<< orphan*/  bacct; } ;
struct bsd_acct_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acct_put (struct bsd_acct_struct*) ; 
 int /*<<< orphan*/  atomic_long_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 struct bsd_acct_struct* to_acct (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bsd_acct_struct *acct_get(struct pid_namespace *ns)
{
	struct bsd_acct_struct *res;
again:
	smp_rmb();
	rcu_read_lock();
	res = to_acct(READ_ONCE(ns->bacct));
	if (!res) {
		rcu_read_unlock();
		return NULL;
	}
	if (!atomic_long_inc_not_zero(&res->count)) {
		rcu_read_unlock();
		cpu_relax();
		goto again;
	}
	rcu_read_unlock();
	mutex_lock(&res->lock);
	if (res != to_acct(READ_ONCE(ns->bacct))) {
		mutex_unlock(&res->lock);
		acct_put(res);
		goto again;
	}
	return res;
}