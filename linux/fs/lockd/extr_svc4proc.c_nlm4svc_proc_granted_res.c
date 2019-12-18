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
struct svc_rqst {struct nlm_res* rq_argp; } ;
struct nlm_res {int /*<<< orphan*/  status; int /*<<< orphan*/  cookie; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  nlmsvc_grant_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsvc_ops ; 
 int /*<<< orphan*/  rpc_success ; 

__attribute__((used)) static __be32
nlm4svc_proc_granted_res(struct svc_rqst *rqstp)
{
	struct nlm_res *argp = rqstp->rq_argp;

        if (!nlmsvc_ops)
                return rpc_success;

        dprintk("lockd: GRANTED_RES   called\n");

        nlmsvc_grant_reply(&argp->cookie, argp->status);
        return rpc_success;
}