#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct svc_rqst {int dummy; } ;
struct TYPE_6__ {int page_len; int len; int buflen; TYPE_2__* head; TYPE_1__* tail; } ;
struct svc_rdma_recv_ctxt {TYPE_3__ rc_arg; scalar_t__ rc_hdr_count; } ;
struct svc_rdma_read_info {int ri_chunklen; scalar_t__ ri_position; struct svc_rdma_recv_ctxt* ri_readctxt; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_5__ {scalar_t__ iov_len; scalar_t__ iov_base; } ;
struct TYPE_4__ {scalar_t__ iov_len; scalar_t__ iov_base; } ;

/* Variables and functions */
 int XDR_QUADLEN (int) ; 
 int svc_rdma_build_read_chunk (struct svc_rqst*,struct svc_rdma_read_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_svcrdma_encode_read (int,scalar_t__) ; 

__attribute__((used)) static int svc_rdma_build_normal_read_chunk(struct svc_rqst *rqstp,
					    struct svc_rdma_read_info *info,
					    __be32 *p)
{
	struct svc_rdma_recv_ctxt *head = info->ri_readctxt;
	int ret;

	ret = svc_rdma_build_read_chunk(rqstp, info, p);
	if (ret < 0)
		goto out;

	trace_svcrdma_encode_read(info->ri_chunklen, info->ri_position);

	head->rc_hdr_count = 0;

	/* Split the Receive buffer between the head and tail
	 * buffers at Read chunk's position. XDR roundup of the
	 * chunk is not included in either the pagelist or in
	 * the tail.
	 */
	head->rc_arg.tail[0].iov_base =
		head->rc_arg.head[0].iov_base + info->ri_position;
	head->rc_arg.tail[0].iov_len =
		head->rc_arg.head[0].iov_len - info->ri_position;
	head->rc_arg.head[0].iov_len = info->ri_position;

	/* Read chunk may need XDR roundup (see RFC 8166, s. 3.4.5.2).
	 *
	 * If the client already rounded up the chunk length, the
	 * length does not change. Otherwise, the length of the page
	 * list is increased to include XDR round-up.
	 *
	 * Currently these chunks always start at page offset 0,
	 * thus the rounded-up length never crosses a page boundary.
	 */
	info->ri_chunklen = XDR_QUADLEN(info->ri_chunklen) << 2;

	head->rc_arg.page_len = info->ri_chunklen;
	head->rc_arg.len += info->ri_chunklen;
	head->rc_arg.buflen += info->ri_chunklen;

out:
	return ret;
}