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
struct nfs4_file {int fi_had_conflict; int /*<<< orphan*/  fi_hash; int /*<<< orphan*/  fi_lo_recalls; int /*<<< orphan*/  fi_lo_states; int /*<<< orphan*/  fi_access; int /*<<< orphan*/  fi_fds; scalar_t__ fi_share_deny; int /*<<< orphan*/ * fi_deleg_file; int /*<<< orphan*/  fi_fhandle; int /*<<< orphan*/  fi_clnt_odstate; int /*<<< orphan*/  fi_delegations; int /*<<< orphan*/  fi_stateids; int /*<<< orphan*/  fi_lock; int /*<<< orphan*/  fi_ref; } ;
struct knfsd_fh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_copy_shallow (int /*<<< orphan*/ *,struct knfsd_fh*) ; 
 int /*<<< orphan*/ * file_hashtbl ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  state_lock ; 

__attribute__((used)) static void nfsd4_init_file(struct knfsd_fh *fh, unsigned int hashval,
				struct nfs4_file *fp)
{
	lockdep_assert_held(&state_lock);

	refcount_set(&fp->fi_ref, 1);
	spin_lock_init(&fp->fi_lock);
	INIT_LIST_HEAD(&fp->fi_stateids);
	INIT_LIST_HEAD(&fp->fi_delegations);
	INIT_LIST_HEAD(&fp->fi_clnt_odstate);
	fh_copy_shallow(&fp->fi_fhandle, fh);
	fp->fi_deleg_file = NULL;
	fp->fi_had_conflict = false;
	fp->fi_share_deny = 0;
	memset(fp->fi_fds, 0, sizeof(fp->fi_fds));
	memset(fp->fi_access, 0, sizeof(fp->fi_access));
#ifdef CONFIG_NFSD_PNFS
	INIT_LIST_HEAD(&fp->fi_lo_states);
	atomic_set(&fp->fi_lo_recalls, 0);
#endif
	hlist_add_head_rcu(&fp->fi_hash, &file_hashtbl[hashval]);
}