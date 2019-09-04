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
struct nfs_pgio_res {int count; int /*<<< orphan*/  server; scalar_t__ fattr; int /*<<< orphan*/  seq_res; int /*<<< orphan*/  op_status; } ;
struct compound_hdr {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int decode_compound_hdr (struct xdr_stream*,struct compound_hdr*) ; 
 int /*<<< orphan*/  decode_getfattr (struct xdr_stream*,scalar_t__,int /*<<< orphan*/ ) ; 
 int decode_putfh (struct xdr_stream*) ; 
 int decode_sequence (struct xdr_stream*,int /*<<< orphan*/ *,struct rpc_rqst*) ; 
 int decode_write (struct xdr_stream*,struct nfs_pgio_res*) ; 

__attribute__((used)) static int nfs4_xdr_dec_write(struct rpc_rqst *rqstp, struct xdr_stream *xdr,
			      void *data)
{
	struct nfs_pgio_res *res = data;
	struct compound_hdr hdr;
	int status;

	status = decode_compound_hdr(xdr, &hdr);
	res->op_status = hdr.status;
	if (status)
		goto out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	if (status)
		goto out;
	status = decode_putfh(xdr);
	if (status)
		goto out;
	status = decode_write(xdr, res);
	if (status)
		goto out;
	if (res->fattr)
		decode_getfattr(xdr, res->fattr, res->server);
	if (!status)
		status = res->count;
out:
	return status;
}