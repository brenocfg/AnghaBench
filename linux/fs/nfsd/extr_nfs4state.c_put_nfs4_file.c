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
struct nfs4_file {int /*<<< orphan*/  fi_rcu; int /*<<< orphan*/  fi_delegations; int /*<<< orphan*/  fi_clnt_odstate; int /*<<< orphan*/  fi_hash; int /*<<< orphan*/  fi_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_free_file_rcu ; 
 scalar_t__ refcount_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  state_lock ; 

void
put_nfs4_file(struct nfs4_file *fi)
{
	might_lock(&state_lock);

	if (refcount_dec_and_lock(&fi->fi_ref, &state_lock)) {
		hlist_del_rcu(&fi->fi_hash);
		spin_unlock(&state_lock);
		WARN_ON_ONCE(!list_empty(&fi->fi_clnt_odstate));
		WARN_ON_ONCE(!list_empty(&fi->fi_delegations));
		call_rcu(&fi->fi_rcu, nfsd4_free_file_rcu);
	}
}