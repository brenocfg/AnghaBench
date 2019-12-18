#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct rpc_rqst {int dummy; } ;
struct nfs_openargs {TYPE_2__* lg_args; int /*<<< orphan*/  open_bitmap; int /*<<< orphan*/  bitmask; scalar_t__ access; int /*<<< orphan*/  fh; int /*<<< orphan*/  seq_args; } ;
struct compound_hdr {int /*<<< orphan*/  replen; int /*<<< orphan*/  minorversion; } ;
struct TYPE_3__ {int /*<<< orphan*/  pglen; int /*<<< orphan*/  pages; } ;
struct TYPE_4__ {TYPE_1__ layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_access (struct xdr_stream*,scalar_t__,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_compound_hdr (struct xdr_stream*,struct rpc_rqst*,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_getfattr_open (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_layoutget (struct xdr_stream*,TYPE_2__*,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_nops (struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_open (struct xdr_stream*,struct nfs_openargs const*,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_putfh (struct xdr_stream*,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_sequence (struct xdr_stream*,int /*<<< orphan*/ *,struct compound_hdr*) ; 
 int /*<<< orphan*/  nfs4_xdr_minorversion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_prepare_reply_pages (struct rpc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs4_xdr_enc_open_noattr(struct rpc_rqst *req,
				     struct xdr_stream *xdr,
				     const void *data)
{
	const struct nfs_openargs *args = data;
	struct compound_hdr hdr = {
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	};

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_open(xdr, args, &hdr);
	if (args->access)
		encode_access(xdr, args->access, &hdr);
	encode_getfattr_open(xdr, args->bitmask, args->open_bitmap, &hdr);
	if (args->lg_args) {
		encode_layoutget(xdr, args->lg_args, &hdr);
		rpc_prepare_reply_pages(req, args->lg_args->layout.pages, 0,
					args->lg_args->layout.pglen,
					hdr.replen);
	}
	encode_nops(&hdr);
}