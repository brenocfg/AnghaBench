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
typedef  scalar_t__ u32 ;
struct xdr_stream {int dummy; } ;
struct xdr_buf {scalar_t__ page_len; } ;
struct rpc_rqst {struct xdr_buf rq_rcv_buf; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  OP_READLINK ; 
 scalar_t__ be32_to_cpup (int /*<<< orphan*/ *) ; 
 int decode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 
 scalar_t__ xdr_read_pages (struct xdr_stream*,scalar_t__) ; 
 int /*<<< orphan*/  xdr_terminate_string (struct xdr_buf*,scalar_t__) ; 

__attribute__((used)) static int decode_readlink(struct xdr_stream *xdr, struct rpc_rqst *req)
{
	struct xdr_buf *rcvbuf = &req->rq_rcv_buf;
	u32 len, recvd;
	__be32 *p;
	int status;

	status = decode_op_hdr(xdr, OP_READLINK);
	if (status)
		return status;

	/* Convert length of symlink */
	p = xdr_inline_decode(xdr, 4);
	if (unlikely(!p))
		return -EIO;
	len = be32_to_cpup(p);
	if (len >= rcvbuf->page_len || len <= 0) {
		dprintk("nfs: server returned giant symlink!\n");
		return -ENAMETOOLONG;
	}
	recvd = xdr_read_pages(xdr, len);
	if (recvd < len) {
		dprintk("NFS: server cheating in readlink reply: "
				"count %u > recvd %u\n", len, recvd);
		return -EIO;
	}
	/*
	 * The XDR encode routine has set things up so that
	 * the link text will be copied directly into the
	 * buffer.  We just have to do overflow-checking,
	 * and and null-terminate the text (the VFS expects
	 * null-termination).
	 */
	xdr_terminate_string(rcvbuf, len);
	return 0;
}