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
struct nfs4_get_lease_time_res {int /*<<< orphan*/  lr_fsinfo; int /*<<< orphan*/  lr_seq_res; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int decode_compound_hdr (struct xdr_stream*,struct compound_hdr*) ; 
 int decode_fsinfo (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int decode_putrootfh (struct xdr_stream*) ; 
 int decode_sequence (struct xdr_stream*,int /*<<< orphan*/ *,struct rpc_rqst*) ; 

__attribute__((used)) static int nfs4_xdr_dec_get_lease_time(struct rpc_rqst *rqstp,
				       struct xdr_stream *xdr,
				       void *data)
{
	struct nfs4_get_lease_time_res *res = data;
	struct compound_hdr hdr;
	int status;

	status = decode_compound_hdr(xdr, &hdr);
	if (!status)
		status = decode_sequence(xdr, &res->lr_seq_res, rqstp);
	if (!status)
		status = decode_putrootfh(xdr);
	if (!status)
		status = decode_fsinfo(xdr, res->lr_fsinfo);
	return status;
}