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
typedef  scalar_t__ uint32_t ;
struct xdr_stream {int dummy; } ;
struct rpc_rqst {int dummy; } ;
struct nfs_getaclargs {int /*<<< orphan*/  acl_len; int /*<<< orphan*/  acl_pages; int /*<<< orphan*/  fh; int /*<<< orphan*/  seq_args; } ;
struct compound_hdr {scalar_t__ replen; int /*<<< orphan*/  minorversion; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const FATTR4_WORD0_ACL ; 
 int /*<<< orphan*/  encode_compound_hdr (struct xdr_stream*,struct rpc_rqst*,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_getattr (struct xdr_stream*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_nops (struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_putfh (struct xdr_stream*,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_sequence (struct xdr_stream*,int /*<<< orphan*/ *,struct compound_hdr*) ; 
 int /*<<< orphan*/  nfs4_xdr_minorversion (int /*<<< orphan*/ *) ; 
 scalar_t__ op_decode_hdr_maxsz ; 
 int /*<<< orphan*/  rpc_prepare_reply_pages (struct rpc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void nfs4_xdr_enc_getacl(struct rpc_rqst *req, struct xdr_stream *xdr,
				const void *data)
{
	const struct nfs_getaclargs *args = data;
	struct compound_hdr hdr = {
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	};
	const __u32 nfs4_acl_bitmap[1] = {
		[0] = FATTR4_WORD0_ACL,
	};
	uint32_t replen;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	replen = hdr.replen + op_decode_hdr_maxsz;
	encode_getattr(xdr, nfs4_acl_bitmap, NULL,
			ARRAY_SIZE(nfs4_acl_bitmap), &hdr);

	rpc_prepare_reply_pages(req, args->acl_pages, 0,
				args->acl_len, replen + 1);
	encode_nops(&hdr);
}