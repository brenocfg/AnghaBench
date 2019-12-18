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
struct nfs_pgio_res {int op_status; int replen; int /*<<< orphan*/  fattr; } ;
typedef  enum nfs_stat { ____Placeholder_nfs_stat } nfs_stat ;

/* Variables and functions */
 int NFS3_OK ; 
 int decode_nfsstat3 (struct xdr_stream*,int*) ; 
 int decode_post_op_attr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int decode_read3resok (struct xdr_stream*,struct nfs_pgio_res*) ; 
 int nfs3_stat_to_errno (int) ; 
 int /*<<< orphan*/  rpc_rqst_userns (struct rpc_rqst*) ; 
 scalar_t__ unlikely (int) ; 
 unsigned int xdr_stream_pos (struct xdr_stream*) ; 

__attribute__((used)) static int nfs3_xdr_dec_read3res(struct rpc_rqst *req, struct xdr_stream *xdr,
				 void *data)
{
	struct nfs_pgio_res *result = data;
	unsigned int pos;
	enum nfs_stat status;
	int error;

	pos = xdr_stream_pos(xdr);
	error = decode_nfsstat3(xdr, &status);
	if (unlikely(error))
		goto out;
	error = decode_post_op_attr(xdr, result->fattr, rpc_rqst_userns(req));
	if (unlikely(error))
		goto out;
	result->op_status = status;
	if (status != NFS3_OK)
		goto out_status;
	result->replen = 4 + ((xdr_stream_pos(xdr) - pos) >> 2);
	error = decode_read3resok(xdr, result);
out:
	return error;
out_status:
	return nfs3_stat_to_errno(status);
}