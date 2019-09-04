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
struct nfs4_setclientid_res {int dummy; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int decode_compound_hdr (struct xdr_stream*,struct compound_hdr*) ; 
 int decode_setclientid (struct xdr_stream*,struct nfs4_setclientid_res*) ; 

__attribute__((used)) static int nfs4_xdr_dec_setclientid(struct rpc_rqst *req,
				    struct xdr_stream *xdr,
				    void *data)
{
	struct nfs4_setclientid_res *res = data;
	struct compound_hdr hdr;
	int status;

	status = decode_compound_hdr(xdr, &hdr);
	if (!status)
		status = decode_setclientid(xdr, res);
	return status;
}