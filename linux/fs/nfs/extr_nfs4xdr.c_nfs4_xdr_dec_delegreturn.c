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
struct xdr_stream {int dummy; } ;
struct rpc_rqst {int dummy; } ;
struct nfs4_delegreturnres {int lr_ret; int /*<<< orphan*/  server; scalar_t__ fattr; scalar_t__ lr_res; int /*<<< orphan*/  seq_res; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int decode_compound_hdr (struct xdr_stream*,struct compound_hdr*) ; 
 int decode_delegreturn (struct xdr_stream*) ; 
 int decode_getfattr (struct xdr_stream*,scalar_t__,int /*<<< orphan*/ ) ; 
 int decode_layoutreturn (struct xdr_stream*,scalar_t__) ; 
 int decode_putfh (struct xdr_stream*) ; 
 int decode_sequence (struct xdr_stream*,int /*<<< orphan*/ *,struct rpc_rqst*) ; 

__attribute__((used)) static int nfs4_xdr_dec_delegreturn(struct rpc_rqst *rqstp,
				    struct xdr_stream *xdr,
				    void *data)
{
	struct nfs4_delegreturnres *res = data;
	struct compound_hdr hdr;
	int status;

	status = decode_compound_hdr(xdr, &hdr);
	if (status)
		goto out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	if (status)
		goto out;
	status = decode_putfh(xdr);
	if (status != 0)
		goto out;
	if (res->lr_res) {
		status = decode_layoutreturn(xdr, res->lr_res);
		res->lr_ret = status;
		if (status)
			goto out;
	}
	if (res->fattr) {
		status = decode_getfattr(xdr, res->fattr, res->server);
		if (status != 0)
			goto out;
	}
	status = decode_delegreturn(xdr);
out:
	return status;
}