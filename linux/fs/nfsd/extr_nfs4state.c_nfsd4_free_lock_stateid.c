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
struct nfs4_stid {int /*<<< orphan*/  sc_stateid; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_file; } ;
struct nfs4_ol_stateid {int /*<<< orphan*/  st_mutex; int /*<<< orphan*/  st_stateowner; TYPE_1__ st_stid; } ;
typedef  int /*<<< orphan*/  stateid_t ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ check_for_locks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ check_stateid_generation (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lockowner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_put_stid (struct nfs4_stid*) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfsd4_lock_ol_stateid (struct nfs4_ol_stateid*) ; 
 scalar_t__ nfserr_locks_held ; 
 struct nfs4_ol_stateid* openlockstateid (struct nfs4_stid*) ; 
 int /*<<< orphan*/  release_lock_stateid (struct nfs4_ol_stateid*) ; 

__attribute__((used)) static __be32
nfsd4_free_lock_stateid(stateid_t *stateid, struct nfs4_stid *s)
{
	struct nfs4_ol_stateid *stp = openlockstateid(s);
	__be32 ret;

	ret = nfsd4_lock_ol_stateid(stp);
	if (ret)
		goto out_put_stid;

	ret = check_stateid_generation(stateid, &s->sc_stateid, 1);
	if (ret)
		goto out;

	ret = nfserr_locks_held;
	if (check_for_locks(stp->st_stid.sc_file,
			    lockowner(stp->st_stateowner)))
		goto out;

	release_lock_stateid(stp);
	ret = nfs_ok;

out:
	mutex_unlock(&stp->st_mutex);
out_put_stid:
	nfs4_put_stid(s);
	return ret;
}