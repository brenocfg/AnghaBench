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
struct nfs3_symlinkargs {int /*<<< orphan*/  fromlen; int /*<<< orphan*/  fromname; int /*<<< orphan*/  fromfh; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  XDRBUF_WRITE ; 
 int /*<<< orphan*/  encode_diropargs3 (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_symlinkdata3 (struct xdr_stream*,struct nfs3_symlinkargs const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_rqst_userns (struct rpc_rqst*) ; 

__attribute__((used)) static void nfs3_xdr_enc_symlink3args(struct rpc_rqst *req,
				      struct xdr_stream *xdr,
				      const void *data)
{
	const struct nfs3_symlinkargs *args = data;

	encode_diropargs3(xdr, args->fromfh, args->fromname, args->fromlen);
	encode_symlinkdata3(xdr, args, rpc_rqst_userns(req));
	xdr->buf->flags |= XDRBUF_WRITE;
}