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
struct nfsd4_setclientid_confirm {int /*<<< orphan*/  sc_clientid; int /*<<< orphan*/  sc_confirm; } ;
union nfsd4_op_u {struct nfsd4_setclientid_confirm setclientid_confirm; } ;
struct svc_rqst {int /*<<< orphan*/  rq_cred; } ;
struct nfsd_net {int /*<<< orphan*/  client_lock; } ;
struct nfsd4_compound_state {int dummy; } ;
struct nfs4_client {int /*<<< orphan*/  cl_cred; int /*<<< orphan*/  cl_name; int /*<<< orphan*/  cl_cb_conn; int /*<<< orphan*/  cl_confirm; } ;
typedef  int /*<<< orphan*/  nfs4_verifier ;
typedef  int /*<<< orphan*/  clientid_t ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ STALE_CLIENTID (int /*<<< orphan*/ *,struct nfsd_net*) ; 
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 scalar_t__ client_has_state (struct nfs4_client*) ; 
 int /*<<< orphan*/  expire_client (struct nfs4_client*) ; 
 struct nfs4_client* find_confirmed_client (int /*<<< orphan*/ *,int,struct nfsd_net*) ; 
 struct nfs4_client* find_confirmed_client_by_name (int /*<<< orphan*/ *,struct nfsd_net*) ; 
 struct nfs4_client* find_unconfirmed_client (int /*<<< orphan*/ *,int,struct nfsd_net*) ; 
 int /*<<< orphan*/  get_client_locked (struct nfs4_client*) ; 
 scalar_t__ mark_client_expired_locked (struct nfs4_client*) ; 
 int /*<<< orphan*/  move_to_confirmed (struct nfs4_client*) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_ok ; 
 int /*<<< orphan*/  nfsd4_change_callback (struct nfs4_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_probe_callback (struct nfs4_client*) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 scalar_t__ nfserr_clid_inuse ; 
 scalar_t__ nfserr_stale_clientid ; 
 int /*<<< orphan*/  put_client_renew_locked (struct nfs4_client*) ; 
 int /*<<< orphan*/  same_creds (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ same_verf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unhash_client_locked (struct nfs4_client*) ; 

__be32
nfsd4_setclientid_confirm(struct svc_rqst *rqstp,
			struct nfsd4_compound_state *cstate,
			union nfsd4_op_u *u)
{
	struct nfsd4_setclientid_confirm *setclientid_confirm =
			&u->setclientid_confirm;
	struct nfs4_client *conf, *unconf;
	struct nfs4_client *old = NULL;
	nfs4_verifier confirm = setclientid_confirm->sc_confirm; 
	clientid_t * clid = &setclientid_confirm->sc_clientid;
	__be32 status;
	struct nfsd_net	*nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	if (STALE_CLIENTID(clid, nn))
		return nfserr_stale_clientid;

	spin_lock(&nn->client_lock);
	conf = find_confirmed_client(clid, false, nn);
	unconf = find_unconfirmed_client(clid, false, nn);
	/*
	 * We try hard to give out unique clientid's, so if we get an
	 * attempt to confirm the same clientid with a different cred,
	 * the client may be buggy; this should never happen.
	 *
	 * Nevertheless, RFC 7530 recommends INUSE for this case:
	 */
	status = nfserr_clid_inuse;
	if (unconf && !same_creds(&unconf->cl_cred, &rqstp->rq_cred))
		goto out;
	if (conf && !same_creds(&conf->cl_cred, &rqstp->rq_cred))
		goto out;
	/* cases below refer to rfc 3530 section 14.2.34: */
	if (!unconf || !same_verf(&confirm, &unconf->cl_confirm)) {
		if (conf && same_verf(&confirm, &conf->cl_confirm)) {
			/* case 2: probable retransmit */
			status = nfs_ok;
		} else /* case 4: client hasn't noticed we rebooted yet? */
			status = nfserr_stale_clientid;
		goto out;
	}
	status = nfs_ok;
	if (conf) { /* case 1: callback update */
		old = unconf;
		unhash_client_locked(old);
		nfsd4_change_callback(conf, &unconf->cl_cb_conn);
	} else { /* case 3: normal case; new or rebooted client */
		old = find_confirmed_client_by_name(&unconf->cl_name, nn);
		if (old) {
			status = nfserr_clid_inuse;
			if (client_has_state(old)
					&& !same_creds(&unconf->cl_cred,
							&old->cl_cred))
				goto out;
			status = mark_client_expired_locked(old);
			if (status) {
				old = NULL;
				goto out;
			}
		}
		move_to_confirmed(unconf);
		conf = unconf;
	}
	get_client_locked(conf);
	spin_unlock(&nn->client_lock);
	nfsd4_probe_callback(conf);
	spin_lock(&nn->client_lock);
	put_client_renew_locked(conf);
out:
	spin_unlock(&nn->client_lock);
	if (old)
		expire_client(old);
	return status;
}