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
typedef  int /*<<< orphan*/  u32 ;
struct xdr_stream {int dummy; } ;
struct rpc_rqst {int dummy; } ;
struct nfs4_get_lease_time_args {int /*<<< orphan*/  la_seq_args; } ;
struct compound_hdr {int /*<<< orphan*/  minorversion; } ;

/* Variables and functions */
 int /*<<< orphan*/  const FATTR4_WORD0_LEASE_TIME ; 
 int /*<<< orphan*/  encode_compound_hdr (struct xdr_stream*,struct rpc_rqst*,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_fsinfo (struct xdr_stream*,int /*<<< orphan*/  const*,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_nops (struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_putrootfh (struct xdr_stream*,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_sequence (struct xdr_stream*,int /*<<< orphan*/ *,struct compound_hdr*) ; 
 int /*<<< orphan*/  nfs4_xdr_minorversion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs4_xdr_enc_get_lease_time(struct rpc_rqst *req,
					struct xdr_stream *xdr,
					const void *data)
{
	const struct nfs4_get_lease_time_args *args = data;
	struct compound_hdr hdr = {
		.minorversion = nfs4_xdr_minorversion(&args->la_seq_args),
	};
	const u32 lease_bitmap[3] = { FATTR4_WORD0_LEASE_TIME };

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->la_seq_args, &hdr);
	encode_putrootfh(xdr, &hdr);
	encode_fsinfo(xdr, lease_bitmap, &hdr);
	encode_nops(&hdr);
}