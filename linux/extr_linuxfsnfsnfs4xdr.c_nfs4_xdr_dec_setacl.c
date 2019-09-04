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
struct nfs_setaclres {int /*<<< orphan*/  seq_res; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int decode_compound_hdr (struct xdr_stream*,struct compound_hdr*) ; 
 int decode_putfh (struct xdr_stream*) ; 
 int decode_sequence (struct xdr_stream*,int /*<<< orphan*/ *,struct rpc_rqst*) ; 
 int decode_setattr (struct xdr_stream*) ; 

__attribute__((used)) static int
nfs4_xdr_dec_setacl(struct rpc_rqst *rqstp, struct xdr_stream *xdr,
		    void *data)
{
	struct nfs_setaclres *res = data;
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
	status = decode_setattr(xdr);
out:
	return status;
}