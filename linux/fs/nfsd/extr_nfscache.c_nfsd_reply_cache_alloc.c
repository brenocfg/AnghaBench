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
struct TYPE_3__ {int /*<<< orphan*/  len; } ;
struct svc_rqst {TYPE_1__ rq_arg; int /*<<< orphan*/  rq_vers; int /*<<< orphan*/  rq_prot; int /*<<< orphan*/  rq_proc; int /*<<< orphan*/  rq_xid; } ;
struct TYPE_4__ {int /*<<< orphan*/  k_csum; int /*<<< orphan*/  k_len; int /*<<< orphan*/  k_vers; int /*<<< orphan*/  k_prot; int /*<<< orphan*/  k_addr; int /*<<< orphan*/  k_proc; int /*<<< orphan*/  k_xid; } ;
struct svc_cacherep {TYPE_2__ c_key; int /*<<< orphan*/  c_lru; int /*<<< orphan*/  c_node; int /*<<< orphan*/  c_type; int /*<<< orphan*/  c_state; } ;
struct sockaddr {int dummy; } ;
struct nfsd_net {int /*<<< orphan*/  drc_slab; } ;
typedef  int /*<<< orphan*/  __wsum ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RC_NOCACHE ; 
 int /*<<< orphan*/  RC_UNUSED ; 
 struct svc_cacherep* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rpc_copy_addr (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_get_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_set_port (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_addr (struct svc_rqst*) ; 

__attribute__((used)) static struct svc_cacherep *
nfsd_reply_cache_alloc(struct svc_rqst *rqstp, __wsum csum,
			struct nfsd_net *nn)
{
	struct svc_cacherep	*rp;

	rp = kmem_cache_alloc(nn->drc_slab, GFP_KERNEL);
	if (rp) {
		rp->c_state = RC_UNUSED;
		rp->c_type = RC_NOCACHE;
		RB_CLEAR_NODE(&rp->c_node);
		INIT_LIST_HEAD(&rp->c_lru);

		memset(&rp->c_key, 0, sizeof(rp->c_key));
		rp->c_key.k_xid = rqstp->rq_xid;
		rp->c_key.k_proc = rqstp->rq_proc;
		rpc_copy_addr((struct sockaddr *)&rp->c_key.k_addr, svc_addr(rqstp));
		rpc_set_port((struct sockaddr *)&rp->c_key.k_addr, rpc_get_port(svc_addr(rqstp)));
		rp->c_key.k_prot = rqstp->rq_prot;
		rp->c_key.k_vers = rqstp->rq_vers;
		rp->c_key.k_len = rqstp->rq_arg.len;
		rp->c_key.k_csum = csum;
	}
	return rp;
}