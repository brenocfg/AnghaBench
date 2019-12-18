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
struct TYPE_3__ {int /*<<< orphan*/  so_id; } ;
struct TYPE_4__ {TYPE_1__ si_opaque; } ;
struct nfs4_stid {TYPE_2__ sc_stateid; int /*<<< orphan*/  sc_count; struct nfs4_client* sc_client; } ;
struct nfs4_ol_stateid {int /*<<< orphan*/  st_locks; struct nfs4_stid st_stid; } ;
struct nfs4_client {int /*<<< orphan*/  cl_stateids; int /*<<< orphan*/  cl_lock; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  close_wq ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_ol_stateid_locked(struct nfs4_ol_stateid *stp,
				       struct list_head *reaplist)
{
	struct nfs4_stid *s = &stp->st_stid;
	struct nfs4_client *clp = s->sc_client;

	lockdep_assert_held(&clp->cl_lock);

	WARN_ON_ONCE(!list_empty(&stp->st_locks));

	if (!refcount_dec_and_test(&s->sc_count)) {
		wake_up_all(&close_wq);
		return;
	}

	idr_remove(&clp->cl_stateids, s->sc_stateid.si_opaque.so_id);
	list_add(&stp->st_locks, reaplist);
}