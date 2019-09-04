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
typedef  int uint32_t ;
struct xdr_stream {int dummy; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_rcv_buf; } ;
struct page {int dummy; } ;
struct nfs4_fs_locations_arg {int /*<<< orphan*/  page; int /*<<< orphan*/  bitmask; int /*<<< orphan*/  name; int /*<<< orphan*/  dir_fh; int /*<<< orphan*/  clientid; scalar_t__ renew; int /*<<< orphan*/  fh; scalar_t__ migration; int /*<<< orphan*/  seq_args; } ;
struct compound_hdr {int replen; int /*<<< orphan*/  minorversion; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  encode_compound_hdr (struct xdr_stream*,struct rpc_rqst*,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_fs_locations (struct xdr_stream*,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_lookup (struct xdr_stream*,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_nops (struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_putfh (struct xdr_stream*,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_renew (struct xdr_stream*,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_sequence (struct xdr_stream*,int /*<<< orphan*/ *,struct compound_hdr*) ; 
 int /*<<< orphan*/  nfs4_xdr_minorversion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_inline_pages (int /*<<< orphan*/ *,int,struct page**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs4_xdr_enc_fs_locations(struct rpc_rqst *req,
				      struct xdr_stream *xdr,
				      const void *data)
{
	const struct nfs4_fs_locations_arg *args = data;
	struct compound_hdr hdr = {
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	};
	uint32_t replen;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	if (args->migration) {
		encode_putfh(xdr, args->fh, &hdr);
		replen = hdr.replen;
		encode_fs_locations(xdr, args->bitmask, &hdr);
		if (args->renew)
			encode_renew(xdr, args->clientid, &hdr);
	} else {
		encode_putfh(xdr, args->dir_fh, &hdr);
		encode_lookup(xdr, args->name, &hdr);
		replen = hdr.replen;
		encode_fs_locations(xdr, args->bitmask, &hdr);
	}

	/* Set up reply kvec to capture returned fs_locations array. */
	xdr_inline_pages(&req->rq_rcv_buf, replen << 2,
			 (struct page **)&args->page, 0, PAGE_SIZE);
	encode_nops(&hdr);
}