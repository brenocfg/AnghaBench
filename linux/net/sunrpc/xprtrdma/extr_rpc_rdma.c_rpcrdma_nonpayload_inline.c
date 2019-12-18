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
struct xdr_buf {TYPE_2__* tail; TYPE_1__* head; } ;
struct TYPE_6__ {scalar_t__ rep_max_inline_recv; } ;
struct rpcrdma_xprt {TYPE_3__ rx_ep; } ;
struct rpc_rqst {struct xdr_buf rq_rcv_buf; } ;
struct TYPE_5__ {scalar_t__ iov_len; } ;
struct TYPE_4__ {scalar_t__ iov_len; } ;

/* Variables and functions */

__attribute__((used)) static bool
rpcrdma_nonpayload_inline(const struct rpcrdma_xprt *r_xprt,
			  const struct rpc_rqst *rqst)
{
	const struct xdr_buf *buf = &rqst->rq_rcv_buf;

	return (buf->head[0].iov_len + buf->tail[0].iov_len) <
		r_xprt->rx_ep.rep_max_inline_recv;
}