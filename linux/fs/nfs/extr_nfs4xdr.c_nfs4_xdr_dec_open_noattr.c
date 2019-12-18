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
struct nfs_openres {scalar_t__ lg_res; int /*<<< orphan*/  server; int /*<<< orphan*/  f_attr; int /*<<< orphan*/  access_result; int /*<<< orphan*/  access_supported; scalar_t__ access_request; int /*<<< orphan*/  seq_res; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  decode_access (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_compound_hdr (struct xdr_stream*,struct compound_hdr*) ; 
 int /*<<< orphan*/  decode_getfattr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_layoutget (struct xdr_stream*,struct rpc_rqst*,scalar_t__) ; 
 int decode_open (struct xdr_stream*,struct nfs_openres*) ; 
 int decode_putfh (struct xdr_stream*) ; 
 int decode_sequence (struct xdr_stream*,int /*<<< orphan*/ *,struct rpc_rqst*) ; 

__attribute__((used)) static int nfs4_xdr_dec_open_noattr(struct rpc_rqst *rqstp,
				    struct xdr_stream *xdr,
				    void *data)
{
	struct nfs_openres *res = data;
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
	status = decode_open(xdr, res);
	if (status)
		goto out;
	if (res->access_request)
		decode_access(xdr, &res->access_supported, &res->access_result);
	decode_getfattr(xdr, res->f_attr, res->server);
	if (res->lg_res)
		decode_layoutget(xdr, rqstp, res->lg_res);
out:
	return status;
}