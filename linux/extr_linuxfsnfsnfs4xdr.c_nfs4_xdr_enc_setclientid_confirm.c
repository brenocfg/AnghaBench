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
struct compound_hdr {int /*<<< orphan*/  nops; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_compound_hdr (struct xdr_stream*,struct rpc_rqst*,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_nops (struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_setclientid_confirm (struct xdr_stream*,struct nfs4_setclientid_res const*,struct compound_hdr*) ; 

__attribute__((used)) static void nfs4_xdr_enc_setclientid_confirm(struct rpc_rqst *req,
					     struct xdr_stream *xdr,
					     const void *data)
{
	const struct nfs4_setclientid_res *arg = data;
	struct compound_hdr hdr = {
		.nops	= 0,
	};

	encode_compound_hdr(xdr, req, &hdr);
	encode_setclientid_confirm(xdr, arg, &hdr);
	encode_nops(&hdr);
}