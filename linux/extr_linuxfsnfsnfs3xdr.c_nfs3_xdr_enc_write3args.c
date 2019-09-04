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
struct xdr_stream {TYPE_1__* buf; } ;
struct rpc_rqst {int dummy; } ;
struct nfs_pgio_args {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  XDRBUF_WRITE ; 
 int /*<<< orphan*/  encode_write3args (struct xdr_stream*,struct nfs_pgio_args const*) ; 

__attribute__((used)) static void nfs3_xdr_enc_write3args(struct rpc_rqst *req,
				    struct xdr_stream *xdr,
				    const void *data)
{
	const struct nfs_pgio_args *args = data;

	encode_write3args(xdr, args);
	xdr->buf->flags |= XDRBUF_WRITE;
}