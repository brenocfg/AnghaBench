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
struct nfsd4_session {struct nfs4_client* se_client; } ;
struct nfsd4_conn {int /*<<< orphan*/  cn_xpt_user; int /*<<< orphan*/  cn_xprt; } ;
struct nfs4_client {int /*<<< orphan*/  cl_lock; scalar_t__ cl_mach_cred; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 struct nfsd4_conn* __nfsd4_find_conn (int /*<<< orphan*/ ,struct nfsd4_session*) ; 
 int /*<<< orphan*/  __nfsd4_hash_conn (struct nfsd4_conn*,struct nfsd4_session*) ; 
 int /*<<< orphan*/  free_conn (struct nfsd4_conn*) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfsd4_conn_lost (int /*<<< orphan*/ *) ; 
 int nfsd4_register_conn (struct nfsd4_conn*) ; 
 int /*<<< orphan*/  nfserr_conn_not_bound_to_session ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32 nfsd4_sequence_check_conn(struct nfsd4_conn *new, struct nfsd4_session *ses)
{
	struct nfs4_client *clp = ses->se_client;
	struct nfsd4_conn *c;
	__be32 status = nfs_ok;
	int ret;

	spin_lock(&clp->cl_lock);
	c = __nfsd4_find_conn(new->cn_xprt, ses);
	if (c)
		goto out_free;
	status = nfserr_conn_not_bound_to_session;
	if (clp->cl_mach_cred)
		goto out_free;
	__nfsd4_hash_conn(new, ses);
	spin_unlock(&clp->cl_lock);
	ret = nfsd4_register_conn(new);
	if (ret)
		/* oops; xprt is already down: */
		nfsd4_conn_lost(&new->cn_xpt_user);
	return nfs_ok;
out_free:
	spin_unlock(&clp->cl_lock);
	free_conn(new);
	return status;
}