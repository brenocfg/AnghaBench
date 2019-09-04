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
struct xdr_buf {int page_len; } ;
struct svcxprt_rdma {int dummy; } ;
struct svc_rdma_write_info {int /*<<< orphan*/  wi_cc; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int svc_rdma_post_chunk_ctxt (int /*<<< orphan*/ *) ; 
 int svc_rdma_send_xdr_pagelist (struct svc_rdma_write_info*,struct xdr_buf*) ; 
 struct svc_rdma_write_info* svc_rdma_write_info_alloc (struct svcxprt_rdma*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_rdma_write_info_free (struct svc_rdma_write_info*) ; 
 int /*<<< orphan*/  trace_svcrdma_encode_write (int) ; 

int svc_rdma_send_write_chunk(struct svcxprt_rdma *rdma, __be32 *wr_ch,
			      struct xdr_buf *xdr)
{
	struct svc_rdma_write_info *info;
	int ret;

	if (!xdr->page_len)
		return 0;

	info = svc_rdma_write_info_alloc(rdma, wr_ch);
	if (!info)
		return -ENOMEM;

	ret = svc_rdma_send_xdr_pagelist(info, xdr);
	if (ret < 0)
		goto out_err;

	ret = svc_rdma_post_chunk_ctxt(&info->wi_cc);
	if (ret < 0)
		goto out_err;

	trace_svcrdma_encode_write(xdr->page_len);
	return xdr->page_len;

out_err:
	svc_rdma_write_info_free(info);
	return ret;
}