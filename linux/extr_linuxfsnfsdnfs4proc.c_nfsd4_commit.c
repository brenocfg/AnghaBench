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
struct nfsd4_commit {int /*<<< orphan*/  co_count; int /*<<< orphan*/  co_offset; int /*<<< orphan*/  co_verf; } ;
union nfsd4_op_u {struct nfsd4_commit commit; } ;
struct svc_rqst {int dummy; } ;
struct nfsd4_compound_state {int /*<<< orphan*/  current_fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 int /*<<< orphan*/  gen_boot_verifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_commit (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
nfsd4_commit(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	     union nfsd4_op_u *u)
{
	struct nfsd4_commit *commit = &u->commit;

	gen_boot_verifier(&commit->co_verf, SVC_NET(rqstp));
	return nfsd_commit(rqstp, &cstate->current_fh, commit->co_offset,
			     commit->co_count);
}