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
struct nlm_res {int /*<<< orphan*/  status; int /*<<< orphan*/  cookie; int /*<<< orphan*/  lock; } ;
struct nlm_host {int dummy; } ;
struct nlm_file {int dummy; } ;
struct nlm_args {int /*<<< orphan*/  lock; int /*<<< orphan*/  cookie; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  nlm4svc_retrieve_args (struct svc_rqst*,struct nlm_args*,struct nlm_host**,struct nlm_file**) ; 
 int /*<<< orphan*/  nlm_drop_reply ; 
 int /*<<< orphan*/  nlm_release_file (struct nlm_file*) ; 
 int /*<<< orphan*/  nlmsvc_release_host (struct nlm_host*) ; 
 int /*<<< orphan*/  nlmsvc_release_lockowner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlmsvc_testlock (struct svc_rqst*,struct nlm_file*,struct nlm_host*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_drop_reply ; 
 int /*<<< orphan*/  rpc_success ; 

__attribute__((used)) static __be32
__nlm4svc_proc_test(struct svc_rqst *rqstp, struct nlm_res *resp)
{
	struct nlm_args *argp = rqstp->rq_argp;
	struct nlm_host	*host;
	struct nlm_file	*file;
	__be32 rc = rpc_success;

	dprintk("lockd: TEST4        called\n");
	resp->cookie = argp->cookie;

	/* Obtain client and file */
	if ((resp->status = nlm4svc_retrieve_args(rqstp, argp, &host, &file)))
		return resp->status == nlm_drop_reply ? rpc_drop_reply :rpc_success;

	/* Now check for conflicting locks */
	resp->status = nlmsvc_testlock(rqstp, file, host, &argp->lock, &resp->lock, &resp->cookie);
	if (resp->status == nlm_drop_reply)
		rc = rpc_drop_reply;
	else
		dprintk("lockd: TEST4        status %d\n", ntohl(resp->status));

	nlmsvc_release_lockowner(&argp->lock);
	nlmsvc_release_host(host);
	nlm_release_file(file);
	return rc;
}