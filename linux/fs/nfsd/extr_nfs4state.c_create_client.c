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
struct xdr_netobj {int dummy; } ;
struct svc_rqst {int /*<<< orphan*/  rq_cred; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct nfsd_net {scalar_t__ clientid_base; } ;
struct TYPE_3__ {scalar_t__ cl_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  cl_ref; } ;
struct nfs4_client {int /*<<< orphan*/  cl_nfsd_dentry; TYPE_1__ cl_clientid; TYPE_2__ cl_nfsdfs; struct net* net; int /*<<< orphan*/ * cl_cb_session; int /*<<< orphan*/  cl_addr; int /*<<< orphan*/  cl_cb_slot_busy; int /*<<< orphan*/  cl_time; int /*<<< orphan*/  cl_cb_null; int /*<<< orphan*/  cl_cred; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_verifier ;

/* Variables and functions */
 int /*<<< orphan*/  NFSPROC4_CLNT_CB_NULL ; 
 struct net* SVC_NET (struct svc_rqst*) ; 
 struct nfs4_client* alloc_client (struct xdr_netobj) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  client_files ; 
 int copy_cred (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_verf (struct nfs4_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_client (struct nfs4_client*) ; 
 int /*<<< orphan*/  gen_clid (struct nfs4_client*,struct nfsd_net*) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,int) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd4_init_cb (int /*<<< orphan*/ *,struct nfs4_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_client_mkdir (struct nfsd_net*,TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 struct sockaddr* svc_addr (struct svc_rqst*) ; 

__attribute__((used)) static struct nfs4_client *create_client(struct xdr_netobj name,
		struct svc_rqst *rqstp, nfs4_verifier *verf)
{
	struct nfs4_client *clp;
	struct sockaddr *sa = svc_addr(rqstp);
	int ret;
	struct net *net = SVC_NET(rqstp);
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);

	clp = alloc_client(name);
	if (clp == NULL)
		return NULL;

	ret = copy_cred(&clp->cl_cred, &rqstp->rq_cred);
	if (ret) {
		free_client(clp);
		return NULL;
	}
	gen_clid(clp, nn);
	kref_init(&clp->cl_nfsdfs.cl_ref);
	nfsd4_init_cb(&clp->cl_cb_null, clp, NULL, NFSPROC4_CLNT_CB_NULL);
	clp->cl_time = get_seconds();
	clear_bit(0, &clp->cl_cb_slot_busy);
	copy_verf(clp, verf);
	memcpy(&clp->cl_addr, sa, sizeof(struct sockaddr_storage));
	clp->cl_cb_session = NULL;
	clp->net = net;
	clp->cl_nfsd_dentry = nfsd_client_mkdir(nn, &clp->cl_nfsdfs,
			clp->cl_clientid.cl_id - nn->clientid_base,
			client_files);
	if (!clp->cl_nfsd_dentry) {
		free_client(clp);
		return NULL;
	}
	return clp;
}