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
struct xdr_buf {int /*<<< orphan*/  len; int /*<<< orphan*/  buflen; scalar_t__ page_base; scalar_t__ page_len; TYPE_2__* tail; TYPE_1__* head; } ;
struct svc_rqst {struct xdr_buf rq_arg; } ;
struct svc_rdma_recv_ctxt {int /*<<< orphan*/  rc_byte_len; int /*<<< orphan*/  rc_recv_buf; } ;
struct TYPE_4__ {scalar_t__ iov_len; int /*<<< orphan*/ * iov_base; } ;
struct TYPE_3__ {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */

__attribute__((used)) static void svc_rdma_build_arg_xdr(struct svc_rqst *rqstp,
				   struct svc_rdma_recv_ctxt *ctxt)
{
	struct xdr_buf *arg = &rqstp->rq_arg;

	arg->head[0].iov_base = ctxt->rc_recv_buf;
	arg->head[0].iov_len = ctxt->rc_byte_len;
	arg->tail[0].iov_base = NULL;
	arg->tail[0].iov_len = 0;
	arg->page_len = 0;
	arg->page_base = 0;
	arg->buflen = ctxt->rc_byte_len;
	arg->len = ctxt->rc_byte_len;
}