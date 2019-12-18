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
struct nfsd4_destroy_clientid {int /*<<< orphan*/  clientid; } ;
union nfsd4_op_u {struct nfsd4_destroy_clientid destroy_clientid; } ;
struct svc_rqst {int dummy; } ;
struct nfsd_net {int /*<<< orphan*/  client_lock; } ;
struct nfsd4_compound_state {int dummy; } ;
struct nfs4_client {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ client_has_state (struct nfs4_client*) ; 
 int /*<<< orphan*/  expire_client (struct nfs4_client*) ; 
 struct nfs4_client* find_confirmed_client (int /*<<< orphan*/ *,int,struct nfsd_net*) ; 
 struct nfs4_client* find_unconfirmed_client (int /*<<< orphan*/ *,int,struct nfsd_net*) ; 
 scalar_t__ mark_client_expired_locked (struct nfs4_client*) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd4_mach_creds_match (struct nfs4_client*,struct svc_rqst*) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 scalar_t__ nfserr_clientid_busy ; 
 scalar_t__ nfserr_stale_clientid ; 
 scalar_t__ nfserr_wrong_cred ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unhash_client_locked (struct nfs4_client*) ; 

__be32
nfsd4_destroy_clientid(struct svc_rqst *rqstp,
		struct nfsd4_compound_state *cstate,
		union nfsd4_op_u *u)
{
	struct nfsd4_destroy_clientid *dc = &u->destroy_clientid;
	struct nfs4_client *conf, *unconf;
	struct nfs4_client *clp = NULL;
	__be32 status = 0;
	struct nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	spin_lock(&nn->client_lock);
	unconf = find_unconfirmed_client(&dc->clientid, true, nn);
	conf = find_confirmed_client(&dc->clientid, true, nn);
	WARN_ON_ONCE(conf && unconf);

	if (conf) {
		if (client_has_state(conf)) {
			status = nfserr_clientid_busy;
			goto out;
		}
		status = mark_client_expired_locked(conf);
		if (status)
			goto out;
		clp = conf;
	} else if (unconf)
		clp = unconf;
	else {
		status = nfserr_stale_clientid;
		goto out;
	}
	if (!nfsd4_mach_creds_match(clp, rqstp)) {
		clp = NULL;
		status = nfserr_wrong_cred;
		goto out;
	}
	unhash_client_locked(clp);
out:
	spin_unlock(&nn->client_lock);
	if (clp)
		expire_client(clp);
	return status;
}