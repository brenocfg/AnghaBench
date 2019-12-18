#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nfsd4_open {struct nfs4_ol_stateid* op_stp; struct nfs4_openowner* op_openowner; } ;
struct TYPE_6__ {TYPE_1__* so_client; int /*<<< orphan*/  so_stateids; } ;
struct nfs4_openowner {TYPE_3__ oo_owner; } ;
struct TYPE_5__ {struct nfs4_file* sc_file; int /*<<< orphan*/  sc_type; int /*<<< orphan*/  sc_count; } ;
struct nfs4_ol_stateid {int /*<<< orphan*/  st_mutex; TYPE_2__ st_stid; int /*<<< orphan*/  st_perfile; int /*<<< orphan*/  st_perstateowner; int /*<<< orphan*/ * st_openstp; scalar_t__ st_deny_bmap; scalar_t__ st_access_bmap; int /*<<< orphan*/  st_stateowner; int /*<<< orphan*/  st_locks; } ;
struct nfs4_file {int /*<<< orphan*/  fi_lock; int /*<<< orphan*/  fi_stateids; } ;
struct TYPE_4__ {int /*<<< orphan*/  cl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS4_OPEN_STID ; 
 int /*<<< orphan*/  OPEN_STATEID_MUTEX ; 
 int /*<<< orphan*/  get_nfs4_file (struct nfs4_file*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_get_stateowner (TYPE_3__*) ; 
 int /*<<< orphan*/  nfs4_put_stid (TYPE_2__*) ; 
 scalar_t__ nfs_ok ; 
 struct nfs4_ol_stateid* nfsd4_find_existing_open (struct nfs4_file*,struct nfsd4_open*) ; 
 scalar_t__ nfsd4_lock_ol_stateid (struct nfs4_ol_stateid*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs4_ol_stateid *
init_open_stateid(struct nfs4_file *fp, struct nfsd4_open *open)
{

	struct nfs4_openowner *oo = open->op_openowner;
	struct nfs4_ol_stateid *retstp = NULL;
	struct nfs4_ol_stateid *stp;

	stp = open->op_stp;
	/* We are moving these outside of the spinlocks to avoid the warnings */
	mutex_init(&stp->st_mutex);
	mutex_lock_nested(&stp->st_mutex, OPEN_STATEID_MUTEX);

retry:
	spin_lock(&oo->oo_owner.so_client->cl_lock);
	spin_lock(&fp->fi_lock);

	retstp = nfsd4_find_existing_open(fp, open);
	if (retstp)
		goto out_unlock;

	open->op_stp = NULL;
	refcount_inc(&stp->st_stid.sc_count);
	stp->st_stid.sc_type = NFS4_OPEN_STID;
	INIT_LIST_HEAD(&stp->st_locks);
	stp->st_stateowner = nfs4_get_stateowner(&oo->oo_owner);
	get_nfs4_file(fp);
	stp->st_stid.sc_file = fp;
	stp->st_access_bmap = 0;
	stp->st_deny_bmap = 0;
	stp->st_openstp = NULL;
	list_add(&stp->st_perstateowner, &oo->oo_owner.so_stateids);
	list_add(&stp->st_perfile, &fp->fi_stateids);

out_unlock:
	spin_unlock(&fp->fi_lock);
	spin_unlock(&oo->oo_owner.so_client->cl_lock);
	if (retstp) {
		/* Handle races with CLOSE */
		if (nfsd4_lock_ol_stateid(retstp) != nfs_ok) {
			nfs4_put_stid(&retstp->st_stid);
			goto retry;
		}
		/* To keep mutex tracking happy */
		mutex_unlock(&stp->st_mutex);
		stp = retstp;
	}
	return stp;
}