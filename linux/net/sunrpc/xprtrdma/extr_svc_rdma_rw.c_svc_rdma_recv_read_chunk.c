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
struct svcxprt_rdma {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  buflen; int /*<<< orphan*/  len; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; } ;
struct svc_rqst {TYPE_2__ rq_arg; } ;
struct TYPE_3__ {int /*<<< orphan*/  buflen; int /*<<< orphan*/  len; scalar_t__ page_len; scalar_t__ page_base; int /*<<< orphan*/  pages; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; } ;
struct svc_rdma_recv_ctxt {TYPE_1__ rc_arg; int /*<<< orphan*/  rc_pages; } ;
struct svc_rdma_read_info {int /*<<< orphan*/  ri_cc; scalar_t__ ri_position; scalar_t__ ri_pageoff; scalar_t__ ri_pageno; struct svc_rdma_recv_ctxt* ri_readctxt; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ be32_to_cpup (int /*<<< orphan*/ *) ; 
 int svc_rdma_build_normal_read_chunk (struct svc_rqst*,struct svc_rdma_read_info*,int /*<<< orphan*/ *) ; 
 int svc_rdma_build_pz_read_chunk (struct svc_rqst*,struct svc_rdma_read_info*,int /*<<< orphan*/ *) ; 
 int svc_rdma_post_chunk_ctxt (int /*<<< orphan*/ *) ; 
 struct svc_rdma_read_info* svc_rdma_read_info_alloc (struct svcxprt_rdma*) ; 
 int /*<<< orphan*/  svc_rdma_read_info_free (struct svc_rdma_read_info*) ; 

int svc_rdma_recv_read_chunk(struct svcxprt_rdma *rdma, struct svc_rqst *rqstp,
			     struct svc_rdma_recv_ctxt *head, __be32 *p)
{
	struct svc_rdma_read_info *info;
	int ret;

	/* The request (with page list) is constructed in
	 * head->rc_arg. Pages involved with RDMA Read I/O are
	 * transferred there.
	 */
	head->rc_arg.head[0] = rqstp->rq_arg.head[0];
	head->rc_arg.tail[0] = rqstp->rq_arg.tail[0];
	head->rc_arg.pages = head->rc_pages;
	head->rc_arg.page_base = 0;
	head->rc_arg.page_len = 0;
	head->rc_arg.len = rqstp->rq_arg.len;
	head->rc_arg.buflen = rqstp->rq_arg.buflen;

	info = svc_rdma_read_info_alloc(rdma);
	if (!info)
		return -ENOMEM;
	info->ri_readctxt = head;
	info->ri_pageno = 0;
	info->ri_pageoff = 0;

	info->ri_position = be32_to_cpup(p + 1);
	if (info->ri_position)
		ret = svc_rdma_build_normal_read_chunk(rqstp, info, p);
	else
		ret = svc_rdma_build_pz_read_chunk(rqstp, info, p);
	if (ret < 0)
		goto out_err;

	ret = svc_rdma_post_chunk_ctxt(&info->ri_cc);
	if (ret < 0)
		goto out_err;
	return 0;

out_err:
	svc_rdma_read_info_free(info);
	return ret;
}