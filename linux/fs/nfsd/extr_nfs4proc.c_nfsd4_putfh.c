#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nfsd4_putfh {int /*<<< orphan*/  pf_fhlen; int /*<<< orphan*/  pf_fhval; } ;
union nfsd4_op_u {struct nfsd4_putfh putfh; } ;
struct svc_rqst {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  fh_base; int /*<<< orphan*/  fh_size; } ;
struct TYPE_5__ {TYPE_1__ fh_handle; } ;
struct nfsd4_compound_state {TYPE_2__ current_fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD_MAY_BYPASS_GSS ; 
 int /*<<< orphan*/  fh_put (TYPE_2__*) ; 
 int /*<<< orphan*/  fh_verify (struct svc_rqst*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
nfsd4_putfh(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	    union nfsd4_op_u *u)
{
	struct nfsd4_putfh *putfh = &u->putfh;

	fh_put(&cstate->current_fh);
	cstate->current_fh.fh_handle.fh_size = putfh->pf_fhlen;
	memcpy(&cstate->current_fh.fh_handle.fh_base, putfh->pf_fhval,
	       putfh->pf_fhlen);
	return fh_verify(rqstp, &cstate->current_fh, 0, NFSD_MAY_BYPASS_GSS);
}