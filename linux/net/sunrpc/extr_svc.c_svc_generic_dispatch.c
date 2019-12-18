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
struct TYPE_4__ {struct kvec* head; } ;
struct TYPE_3__ {struct kvec* head; } ;
struct svc_rqst {int /*<<< orphan*/  rq_flags; struct svc_procedure* rq_procinfo; TYPE_2__ rq_res; TYPE_1__ rq_arg; } ;
struct svc_procedure {int /*<<< orphan*/  (* pc_encode ) (struct svc_rqst*,scalar_t__) ;int /*<<< orphan*/  (* pc_func ) (struct svc_rqst*) ;int /*<<< orphan*/  (* pc_decode ) (struct svc_rqst*,scalar_t__) ;} ;
struct kvec {scalar_t__ iov_len; scalar_t__ iov_base; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  RQ_AUTHERR ; 
 int /*<<< orphan*/  RQ_DROPME ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  rpc_drop_reply ; 
 int /*<<< orphan*/  rpc_garbage_args ; 
 int /*<<< orphan*/  rpc_success ; 
 int /*<<< orphan*/  rpc_system_err ; 
 int /*<<< orphan*/  stub1 (struct svc_rqst*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct svc_rqst*) ; 
 int /*<<< orphan*/  stub3 (struct svc_rqst*,scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
svc_generic_dispatch(struct svc_rqst *rqstp, __be32 *statp)
{
	struct kvec *argv = &rqstp->rq_arg.head[0];
	struct kvec *resv = &rqstp->rq_res.head[0];
	const struct svc_procedure *procp = rqstp->rq_procinfo;

	/*
	 * Decode arguments
	 * XXX: why do we ignore the return value?
	 */
	if (procp->pc_decode &&
	    !procp->pc_decode(rqstp, argv->iov_base)) {
		*statp = rpc_garbage_args;
		return 1;
	}

	*statp = procp->pc_func(rqstp);

	if (*statp == rpc_drop_reply ||
	    test_bit(RQ_DROPME, &rqstp->rq_flags))
		return 0;

	if (test_bit(RQ_AUTHERR, &rqstp->rq_flags))
		return 1;

	if (*statp != rpc_success)
		return 1;

	/* Encode reply */
	if (procp->pc_encode &&
	    !procp->pc_encode(rqstp, resv->iov_base + resv->iov_len)) {
		dprintk("svc: failed to encode reply\n");
		/* serv->sv_stats->rpcsystemerr++; */
		*statp = rpc_system_err;
	}
	return 1;
}