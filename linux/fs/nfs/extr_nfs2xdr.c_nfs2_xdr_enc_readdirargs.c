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
struct nfs_readdirargs {int /*<<< orphan*/  count; int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_readdirres_sz ; 
 int /*<<< orphan*/  encode_readdirargs (struct xdr_stream*,struct nfs_readdirargs const*) ; 
 int /*<<< orphan*/  rpc_prepare_reply_pages (struct rpc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs2_xdr_enc_readdirargs(struct rpc_rqst *req,
				     struct xdr_stream *xdr,
				     const void *data)
{
	const struct nfs_readdirargs *args = data;

	encode_readdirargs(xdr, args);
	rpc_prepare_reply_pages(req, args->pages, 0,
				args->count, NFS_readdirres_sz);
}