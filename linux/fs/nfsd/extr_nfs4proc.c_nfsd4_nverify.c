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
union nfsd4_op_u {int /*<<< orphan*/  verify; } ;
struct svc_rqst {int dummy; } ;
struct nfsd4_compound_state {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ _nfsd4_verify (struct svc_rqst*,struct nfsd4_compound_state*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfserr_not_same ; 

__attribute__((used)) static __be32
nfsd4_nverify(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	      union nfsd4_op_u *u)
{
	__be32 status;

	status = _nfsd4_verify(rqstp, cstate, &u->verify);
	return status == nfserr_not_same ? nfs_ok : status;
}