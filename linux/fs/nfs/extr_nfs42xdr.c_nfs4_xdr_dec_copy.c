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
struct rpc_rqst {int dummy; } ;
struct TYPE_2__ {scalar_t__ verf; } ;
struct nfs42_copy_res {TYPE_1__ commit_res; int /*<<< orphan*/  seq_res; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int decode_commit (struct xdr_stream*,TYPE_1__*) ; 
 int decode_compound_hdr (struct xdr_stream*,struct compound_hdr*) ; 
 int decode_copy (struct xdr_stream*,struct nfs42_copy_res*) ; 
 int decode_putfh (struct xdr_stream*) ; 
 int decode_savefh (struct xdr_stream*) ; 
 int decode_sequence (struct xdr_stream*,int /*<<< orphan*/ *,struct rpc_rqst*) ; 

__attribute__((used)) static int nfs4_xdr_dec_copy(struct rpc_rqst *rqstp,
			     struct xdr_stream *xdr,
			     void *data)
{
	struct nfs42_copy_res *res = data;
	struct compound_hdr hdr;
	int status;

	status = decode_compound_hdr(xdr, &hdr);
	if (status)
		goto out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	if (status)
		goto out;
	status = decode_putfh(xdr);
	if (status)
		goto out;
	status = decode_savefh(xdr);
	if (status)
		goto out;
	status = decode_putfh(xdr);
	if (status)
		goto out;
	status = decode_copy(xdr, res);
	if (status)
		goto out;
	if (res->commit_res.verf)
		status = decode_commit(xdr, &res->commit_res);
out:
	return status;
}