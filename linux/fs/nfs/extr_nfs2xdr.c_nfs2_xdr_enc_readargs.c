#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct rpc_rqst {TYPE_1__ rq_rcv_buf; } ;
struct nfs_pgio_args {int /*<<< orphan*/  count; int /*<<< orphan*/  pgbase; int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_readres_sz ; 
 int /*<<< orphan*/  XDRBUF_READ ; 
 int /*<<< orphan*/  encode_readargs (struct xdr_stream*,struct nfs_pgio_args const*) ; 
 int /*<<< orphan*/  rpc_prepare_reply_pages (struct rpc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs2_xdr_enc_readargs(struct rpc_rqst *req,
				  struct xdr_stream *xdr,
				  const void *data)
{
	const struct nfs_pgio_args *args = data;

	encode_readargs(xdr, args);
	rpc_prepare_reply_pages(req, args->pages, args->pgbase,
				args->count, NFS_readres_sz);
	req->rq_rcv_buf.flags |= XDRBUF_READ;
}