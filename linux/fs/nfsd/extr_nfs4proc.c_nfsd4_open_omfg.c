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
struct svc_rqst {int dummy; } ;
struct nfsd4_open {int /*<<< orphan*/  op_xdr_error; } ;
struct TYPE_2__ {struct nfsd4_open open; } ;
struct nfsd4_op {TYPE_1__ u; int /*<<< orphan*/  status; } ;
struct nfsd4_compound_state {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ nfsd4_has_session (struct nfsd4_compound_state*) ; 
 int /*<<< orphan*/  nfsd4_open (struct svc_rqst*,struct nfsd4_compound_state*,TYPE_1__*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seqid_mutating_err (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 nfsd4_open_omfg(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate, struct nfsd4_op *op)
{
	struct nfsd4_open *open = &op->u.open;

	if (!seqid_mutating_err(ntohl(op->status)))
		return op->status;
	if (nfsd4_has_session(cstate))
		return op->status;
	open->op_xdr_error = op->status;
	return nfsd4_open(rqstp, cstate, &op->u);
}