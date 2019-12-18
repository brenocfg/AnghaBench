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
struct nfs_createargs {int /*<<< orphan*/  sattr; int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  fh; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_diropargs (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_sattr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_rqst_userns (struct rpc_rqst*) ; 

__attribute__((used)) static void nfs2_xdr_enc_createargs(struct rpc_rqst *req,
				    struct xdr_stream *xdr,
				    const void *data)
{
	const struct nfs_createargs *args = data;

	encode_diropargs(xdr, args->fh, args->name, args->len);
	encode_sattr(xdr, args->sattr, rpc_rqst_userns(req));
}