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
struct svc_rqst {struct nlm_args* rq_argp; } ;
struct nlm_res {int /*<<< orphan*/  status; int /*<<< orphan*/  cookie; } ;
struct nlm_args {int /*<<< orphan*/  lock; int /*<<< orphan*/  cookie; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  nlmclnt_grant (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_success ; 
 int /*<<< orphan*/  svc_addr (struct svc_rqst*) ; 

__attribute__((used)) static __be32
__nlm4svc_proc_granted(struct svc_rqst *rqstp, struct nlm_res *resp)
{
	struct nlm_args *argp = rqstp->rq_argp;

	resp->cookie = argp->cookie;

	dprintk("lockd: GRANTED       called\n");
	resp->status = nlmclnt_grant(svc_addr(rqstp), &argp->lock);
	dprintk("lockd: GRANTED       status %d\n", ntohl(resp->status));
	return rpc_success;
}