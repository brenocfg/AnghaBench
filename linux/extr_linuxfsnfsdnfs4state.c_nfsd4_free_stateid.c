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
struct nfsd4_free_stateid {int /*<<< orphan*/  fr_stateid; } ;
union nfsd4_op_u {struct nfsd4_free_stateid free_stateid; } ;
struct svc_rqst {int dummy; } ;
struct nfsd4_compound_state {TYPE_1__* session; } ;
struct nfs4_stid {int sc_type; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_count; int /*<<< orphan*/  sc_stateid; } ;
struct nfs4_delegation {int /*<<< orphan*/  dl_recall_lru; } ;
struct nfs4_client {int /*<<< orphan*/  cl_lock; } ;
typedef  int /*<<< orphan*/  stateid_t ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct nfs4_client* se_client; } ;

/* Variables and functions */
#define  NFS4_DELEG_STID 131 
#define  NFS4_LOCK_STID 130 
#define  NFS4_OPEN_STID 129 
#define  NFS4_REVOKED_DELEG_STID 128 
 int /*<<< orphan*/  check_stateid_generation (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct nfs4_delegation* delegstateid (struct nfs4_stid*) ; 
 struct nfs4_stid* find_stateid_locked (struct nfs4_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_put_stid (struct nfs4_stid*) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfsd4_free_lock_stateid (int /*<<< orphan*/ *,struct nfs4_stid*) ; 
 int /*<<< orphan*/  nfserr_bad_stateid ; 
 int /*<<< orphan*/  nfserr_locks_held ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__be32
nfsd4_free_stateid(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
		   union nfsd4_op_u *u)
{
	struct nfsd4_free_stateid *free_stateid = &u->free_stateid;
	stateid_t *stateid = &free_stateid->fr_stateid;
	struct nfs4_stid *s;
	struct nfs4_delegation *dp;
	struct nfs4_client *cl = cstate->session->se_client;
	__be32 ret = nfserr_bad_stateid;

	spin_lock(&cl->cl_lock);
	s = find_stateid_locked(cl, stateid);
	if (!s)
		goto out_unlock;
	spin_lock(&s->sc_lock);
	switch (s->sc_type) {
	case NFS4_DELEG_STID:
		ret = nfserr_locks_held;
		break;
	case NFS4_OPEN_STID:
		ret = check_stateid_generation(stateid, &s->sc_stateid, 1);
		if (ret)
			break;
		ret = nfserr_locks_held;
		break;
	case NFS4_LOCK_STID:
		spin_unlock(&s->sc_lock);
		refcount_inc(&s->sc_count);
		spin_unlock(&cl->cl_lock);
		ret = nfsd4_free_lock_stateid(stateid, s);
		goto out;
	case NFS4_REVOKED_DELEG_STID:
		spin_unlock(&s->sc_lock);
		dp = delegstateid(s);
		list_del_init(&dp->dl_recall_lru);
		spin_unlock(&cl->cl_lock);
		nfs4_put_stid(s);
		ret = nfs_ok;
		goto out;
	/* Default falls through and returns nfserr_bad_stateid */
	}
	spin_unlock(&s->sc_lock);
out_unlock:
	spin_unlock(&cl->cl_lock);
out:
	return ret;
}