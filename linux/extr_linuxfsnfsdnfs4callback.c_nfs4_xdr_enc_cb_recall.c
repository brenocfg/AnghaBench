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
struct nfsd4_callback {TYPE_1__* cb_clp; } ;
struct nfs4_delegation {int dummy; } ;
struct nfs4_cb_compound_hdr {int /*<<< orphan*/  minorversion; int /*<<< orphan*/  ident; } ;
struct TYPE_2__ {int /*<<< orphan*/  cl_minorversion; int /*<<< orphan*/  cl_cb_ident; } ;

/* Variables and functions */
 struct nfs4_delegation* cb_to_delegation (struct nfsd4_callback const*) ; 
 int /*<<< orphan*/  encode_cb_compound4args (struct xdr_stream*,struct nfs4_cb_compound_hdr*) ; 
 int /*<<< orphan*/  encode_cb_nops (struct nfs4_cb_compound_hdr*) ; 
 int /*<<< orphan*/  encode_cb_recall4args (struct xdr_stream*,struct nfs4_delegation const*,struct nfs4_cb_compound_hdr*) ; 
 int /*<<< orphan*/  encode_cb_sequence4args (struct xdr_stream*,struct nfsd4_callback const*,struct nfs4_cb_compound_hdr*) ; 

__attribute__((used)) static void nfs4_xdr_enc_cb_recall(struct rpc_rqst *req, struct xdr_stream *xdr,
				   const void *data)
{
	const struct nfsd4_callback *cb = data;
	const struct nfs4_delegation *dp = cb_to_delegation(cb);
	struct nfs4_cb_compound_hdr hdr = {
		.ident = cb->cb_clp->cl_cb_ident,
		.minorversion = cb->cb_clp->cl_minorversion,
	};

	encode_cb_compound4args(xdr, &hdr);
	encode_cb_sequence4args(xdr, cb, &hdr);
	encode_cb_recall4args(xdr, dp, &hdr);
	encode_cb_nops(&hdr);
}