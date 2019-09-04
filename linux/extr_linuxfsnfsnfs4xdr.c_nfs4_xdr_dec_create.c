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
struct nfs4_create_res {int /*<<< orphan*/  server; int /*<<< orphan*/  label; int /*<<< orphan*/  fattr; int /*<<< orphan*/  fh; int /*<<< orphan*/  dir_cinfo; int /*<<< orphan*/  seq_res; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int decode_compound_hdr (struct xdr_stream*,struct compound_hdr*) ; 
 int decode_create (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decode_getfattr_label (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int decode_getfh (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int decode_putfh (struct xdr_stream*) ; 
 int decode_sequence (struct xdr_stream*,int /*<<< orphan*/ *,struct rpc_rqst*) ; 

__attribute__((used)) static int nfs4_xdr_dec_create(struct rpc_rqst *rqstp, struct xdr_stream *xdr,
			       void *data)
{
	struct nfs4_create_res *res = data;
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
	status = decode_create(xdr, &res->dir_cinfo);
	if (status)
		goto out;
	status = decode_getfh(xdr, res->fh);
	if (status)
		goto out;
	decode_getfattr_label(xdr, res->fattr, res->label, res->server);
out:
	return status;
}