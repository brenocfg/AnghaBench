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
typedef  int u32 ;
struct svc_rqst {struct nfsd4_compoundargs* rq_argp; struct nfsd4_compoundres* rq_resp; } ;
struct nfsd4_op {int /*<<< orphan*/  opnum; } ;
struct nfsd4_compound_state {int spo_must_allowed; TYPE_2__* clp; int /*<<< orphan*/  minorversion; } ;
struct nfsd4_compoundres {int opcnt; struct nfsd4_compound_state cstate; } ;
struct nfsd4_compoundargs {int opcnt; struct nfsd4_op* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  longs; } ;
struct nfs4_op_map {TYPE_1__ u; } ;
struct TYPE_4__ {scalar_t__ cl_mach_cred; struct nfs4_op_map cl_spo_must_allow; } ;

/* Variables and functions */
 scalar_t__ nfsd4_mach_creds_match (TYPE_2__*,struct svc_rqst*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool nfsd4_spo_must_allow(struct svc_rqst *rqstp)
{
	struct nfsd4_compoundres *resp = rqstp->rq_resp;
	struct nfsd4_compoundargs *argp = rqstp->rq_argp;
	struct nfsd4_op *this = &argp->ops[resp->opcnt - 1];
	struct nfsd4_compound_state *cstate = &resp->cstate;
	struct nfs4_op_map *allow = &cstate->clp->cl_spo_must_allow;
	u32 opiter;

	if (!cstate->minorversion)
		return false;

	if (cstate->spo_must_allowed == true)
		return true;

	opiter = resp->opcnt;
	while (opiter < argp->opcnt) {
		this = &argp->ops[opiter++];
		if (test_bit(this->opnum, allow->u.longs) &&
			cstate->clp->cl_mach_cred &&
			nfsd4_mach_creds_match(cstate->clp, rqstp)) {
			cstate->spo_must_allowed = true;
			return true;
		}
	}
	cstate->spo_must_allowed = false;
	return false;
}