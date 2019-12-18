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
struct rpc_cred {TYPE_1__* cr_ops; int /*<<< orphan*/  cr_count; int /*<<< orphan*/  cr_flags; int /*<<< orphan*/  cr_expire; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* crdestroy ) (struct rpc_cred*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RPCAUTH_CRED_HASHED ; 
 int /*<<< orphan*/  RPCAUTH_CRED_UPTODATE ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpcauth_lru_add (struct rpc_cred*) ; 
 int /*<<< orphan*/  rpcauth_lru_remove (struct rpc_cred*) ; 
 scalar_t__ rpcauth_unhash_cred (struct rpc_cred*) ; 
 int /*<<< orphan*/  stub1 (struct rpc_cred*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void
put_rpccred(struct rpc_cred *cred)
{
	if (cred == NULL)
		return;
	rcu_read_lock();
	if (refcount_dec_and_test(&cred->cr_count))
		goto destroy;
	if (refcount_read(&cred->cr_count) != 1 ||
	    !test_bit(RPCAUTH_CRED_HASHED, &cred->cr_flags))
		goto out;
	if (test_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags) != 0) {
		cred->cr_expire = jiffies;
		rpcauth_lru_add(cred);
		/* Race breaker */
		if (unlikely(!test_bit(RPCAUTH_CRED_HASHED, &cred->cr_flags)))
			rpcauth_lru_remove(cred);
	} else if (rpcauth_unhash_cred(cred)) {
		rpcauth_lru_remove(cred);
		if (refcount_dec_and_test(&cred->cr_count))
			goto destroy;
	}
out:
	rcu_read_unlock();
	return;
destroy:
	rcu_read_unlock();
	cred->cr_ops->crdestroy(cred);
}