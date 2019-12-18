#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  cl_id; int /*<<< orphan*/  cl_boot; } ;
struct xdr_netobj {int dummy; } ;
struct nfsd4_setclientid {TYPE_3__ se_confirm; TYPE_1__ se_clientid; int /*<<< orphan*/  se_verf; struct xdr_netobj se_name; } ;
union nfsd4_op_u {struct nfsd4_setclientid setclientid; } ;
struct svc_rqst {int /*<<< orphan*/  rq_cred; } ;
struct sockaddr {int dummy; } ;
struct nfsd_net {int /*<<< orphan*/  client_lock; } ;
struct nfsd4_compound_state {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  cl_id; int /*<<< orphan*/  cl_boot; } ;
struct nfs4_client {TYPE_4__ cl_confirm; TYPE_2__ cl_clientid; scalar_t__ cl_minorversion; int /*<<< orphan*/  cl_verifier; int /*<<< orphan*/  cl_addr; int /*<<< orphan*/  cl_cred; } ;
typedef  int /*<<< orphan*/  nfs4_verifier ;
typedef  int /*<<< orphan*/  addr_str ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 int /*<<< orphan*/  add_to_unconfirmed (struct nfs4_client*) ; 
 scalar_t__ client_has_state (struct nfs4_client*) ; 
 scalar_t__ clp_used_exchangeid (struct nfs4_client*) ; 
 int /*<<< orphan*/  copy_clid (struct nfs4_client*,struct nfs4_client*) ; 
 struct nfs4_client* create_client (struct xdr_netobj,struct svc_rqst*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,char*) ; 
 int /*<<< orphan*/  expire_client (struct nfs4_client*) ; 
 struct nfs4_client* find_confirmed_client_by_name (struct xdr_netobj*,struct nfsd_net*) ; 
 struct nfs4_client* find_unconfirmed_client_by_name (struct xdr_netobj*,struct nfsd_net*) ; 
 int /*<<< orphan*/  free_client (struct nfs4_client*) ; 
 int /*<<< orphan*/  gen_callback (struct nfs4_client*,struct nfsd4_setclientid*,struct svc_rqst*) ; 
 int /*<<< orphan*/  gen_confirm (struct nfs4_client*,struct nfsd_net*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  nfserr_clid_inuse ; 
 int /*<<< orphan*/  nfserr_jukebox ; 
 int /*<<< orphan*/  rpc_ntop (struct sockaddr*,char*,int) ; 
 int /*<<< orphan*/  same_creds (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ same_verf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unhash_client_locked (struct nfs4_client*) ; 

__be32
nfsd4_setclientid(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
		  union nfsd4_op_u *u)
{
	struct nfsd4_setclientid *setclid = &u->setclientid;
	struct xdr_netobj 	clname = setclid->se_name;
	nfs4_verifier		clverifier = setclid->se_verf;
	struct nfs4_client	*conf, *new;
	struct nfs4_client	*unconf = NULL;
	__be32 			status;
	struct nfsd_net		*nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	new = create_client(clname, rqstp, &clverifier);
	if (new == NULL)
		return nfserr_jukebox;
	/* Cases below refer to rfc 3530 section 14.2.33: */
	spin_lock(&nn->client_lock);
	conf = find_confirmed_client_by_name(&clname, nn);
	if (conf && client_has_state(conf)) {
		/* case 0: */
		status = nfserr_clid_inuse;
		if (clp_used_exchangeid(conf))
			goto out;
		if (!same_creds(&conf->cl_cred, &rqstp->rq_cred)) {
			char addr_str[INET6_ADDRSTRLEN];
			rpc_ntop((struct sockaddr *) &conf->cl_addr, addr_str,
				 sizeof(addr_str));
			dprintk("NFSD: setclientid: string in use by client "
				"at %s\n", addr_str);
			goto out;
		}
	}
	unconf = find_unconfirmed_client_by_name(&clname, nn);
	if (unconf)
		unhash_client_locked(unconf);
	if (conf && same_verf(&conf->cl_verifier, &clverifier)) {
		/* case 1: probable callback update */
		copy_clid(new, conf);
		gen_confirm(new, nn);
	} else /* case 4 (new client) or cases 2, 3 (client reboot): */
		;
	new->cl_minorversion = 0;
	gen_callback(new, setclid, rqstp);
	add_to_unconfirmed(new);
	setclid->se_clientid.cl_boot = new->cl_clientid.cl_boot;
	setclid->se_clientid.cl_id = new->cl_clientid.cl_id;
	memcpy(setclid->se_confirm.data, new->cl_confirm.data, sizeof(setclid->se_confirm.data));
	new = NULL;
	status = nfs_ok;
out:
	spin_unlock(&nn->client_lock);
	if (new)
		free_client(new);
	if (unconf)
		expire_client(unconf);
	return status;
}