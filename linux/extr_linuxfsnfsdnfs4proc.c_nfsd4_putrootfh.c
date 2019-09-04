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
typedef  union nfsd4_op_u {int dummy; } nfsd4_op_u ;
struct svc_rqst {int dummy; } ;
struct nfsd4_compound_state {int /*<<< orphan*/  current_fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  exp_pseudoroot (struct svc_rqst*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fh_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_putrootfh(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
		union nfsd4_op_u *u)
{
	__be32 status;

	fh_put(&cstate->current_fh);
	status = exp_pseudoroot(rqstp, &cstate->current_fh);
	return status;
}