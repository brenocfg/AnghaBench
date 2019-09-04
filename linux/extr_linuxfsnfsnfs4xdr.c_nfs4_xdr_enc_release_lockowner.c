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
struct nfs_release_lockowner_args {int /*<<< orphan*/  lock_owner; } ;
struct compound_hdr {int /*<<< orphan*/  minorversion; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_compound_hdr (struct xdr_stream*,struct rpc_rqst*,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_nops (struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_release_lockowner (struct xdr_stream*,int /*<<< orphan*/ *,struct compound_hdr*) ; 

__attribute__((used)) static void nfs4_xdr_enc_release_lockowner(struct rpc_rqst *req,
					   struct xdr_stream *xdr,
					   const void *data)
{
	const struct nfs_release_lockowner_args *args = data;
	struct compound_hdr hdr = {
		.minorversion = 0,
	};

	encode_compound_hdr(xdr, req, &hdr);
	encode_release_lockowner(xdr, &args->lock_owner, &hdr);
	encode_nops(&hdr);
}