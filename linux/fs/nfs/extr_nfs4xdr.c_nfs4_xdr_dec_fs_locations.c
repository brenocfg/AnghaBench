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
struct nfs4_fs_locations_res {TYPE_1__* fs_locations; scalar_t__ renew; scalar_t__ migration; int /*<<< orphan*/  seq_res; } ;
struct compound_hdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  server; int /*<<< orphan*/  fattr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int decode_compound_hdr (struct xdr_stream*,struct compound_hdr*) ; 
 int decode_getfattr_generic (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int decode_lookup (struct xdr_stream*) ; 
 int decode_putfh (struct xdr_stream*) ; 
 int decode_renew (struct xdr_stream*) ; 
 int decode_sequence (struct xdr_stream*,int /*<<< orphan*/ *,struct rpc_rqst*) ; 
 int /*<<< orphan*/  xdr_enter_page (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs4_xdr_dec_fs_locations(struct rpc_rqst *req,
				     struct xdr_stream *xdr,
				     void *data)
{
	struct nfs4_fs_locations_res *res = data;
	struct compound_hdr hdr;
	int status;

	status = decode_compound_hdr(xdr, &hdr);
	if (status)
		goto out;
	status = decode_sequence(xdr, &res->seq_res, req);
	if (status)
		goto out;
	status = decode_putfh(xdr);
	if (status)
		goto out;
	if (res->migration) {
		xdr_enter_page(xdr, PAGE_SIZE);
		status = decode_getfattr_generic(xdr,
					&res->fs_locations->fattr,
					 NULL, res->fs_locations,
					 NULL, res->fs_locations->server);
		if (status)
			goto out;
		if (res->renew)
			status = decode_renew(xdr);
	} else {
		status = decode_lookup(xdr);
		if (status)
			goto out;
		xdr_enter_page(xdr, PAGE_SIZE);
		status = decode_getfattr_generic(xdr,
					&res->fs_locations->fattr,
					 NULL, res->fs_locations,
					 NULL, res->fs_locations->server);
	}
out:
	return status;
}