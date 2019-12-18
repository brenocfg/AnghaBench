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
struct nlm_host {scalar_t__ h_nsmstate; } ;
struct nlm_file {int dummy; } ;
struct nlm_args {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  reclaim; int /*<<< orphan*/  cookie; int /*<<< orphan*/  block; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  cast_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  nlm_drop_reply ; 
 int /*<<< orphan*/  nlm_lck_denied_nolocks ; 
 int /*<<< orphan*/  nlm_release_file (struct nlm_file*) ; 
 int /*<<< orphan*/  nlmsvc_lock (struct svc_rqst*,struct nlm_file*,struct nlm_host*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsvc_release_host (struct nlm_host*) ; 
 int /*<<< orphan*/  nlmsvc_release_lockowner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlmsvc_retrieve_args (struct svc_rqst*,struct nlm_args*,struct nlm_host**,struct nlm_file**) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_drop_reply ; 
 int /*<<< orphan*/  rpc_success ; 

__attribute__((used)) static __be32
__nlmsvc_proc_lock(struct svc_rqst *rqstp, struct nlm_res *resp)
{
	struct nlm_args *argp = rqstp->rq_argp;
	struct nlm_host	*host;
	struct nlm_file	*file;
	__be32 rc = rpc_success;

	dprintk("lockd: LOCK          called\n");

	resp->cookie = argp->cookie;

	/* Obtain client and file */
	if ((resp->status = nlmsvc_retrieve_args(rqstp, argp, &host, &file)))
		return resp->status == nlm_drop_reply ? rpc_drop_reply :rpc_success;

#if 0
	/* If supplied state doesn't match current state, we assume it's
	 * an old request that time-warped somehow. Any error return would
	 * do in this case because it's irrelevant anyway.
	 *
	 * NB: We don't retrieve the remote host's state yet.
	 */
	if (host->h_nsmstate && host->h_nsmstate != argp->state) {
		resp->status = nlm_lck_denied_nolocks;
	} else
#endif

	/* Now try to lock the file */
	resp->status = cast_status(nlmsvc_lock(rqstp, file, host, &argp->lock,
					       argp->block, &argp->cookie,
					       argp->reclaim));
	if (resp->status == nlm_drop_reply)
		rc = rpc_drop_reply;
	else
		dprintk("lockd: LOCK         status %d\n", ntohl(resp->status));

	nlmsvc_release_lockowner(&argp->lock);
	nlmsvc_release_host(host);
	nlm_release_file(file);
	return rc;
}