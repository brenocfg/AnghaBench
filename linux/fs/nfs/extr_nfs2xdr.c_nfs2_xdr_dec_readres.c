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
struct nfs_pgio_res {int op_status; int /*<<< orphan*/  fattr; } ;
typedef  enum nfs_stat { ____Placeholder_nfs_stat } nfs_stat ;

/* Variables and functions */
 int NFS_OK ; 
 int decode_fattr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int decode_nfsdata (struct xdr_stream*,struct nfs_pgio_res*) ; 
 int decode_stat (struct xdr_stream*,int*) ; 
 int nfs_stat_to_errno (int) ; 
 int /*<<< orphan*/  rpc_rqst_userns (struct rpc_rqst*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nfs2_xdr_dec_readres(struct rpc_rqst *req, struct xdr_stream *xdr,
				void *data)
{
	struct nfs_pgio_res *result = data;
	enum nfs_stat status;
	int error;

	error = decode_stat(xdr, &status);
	if (unlikely(error))
		goto out;
	result->op_status = status;
	if (status != NFS_OK)
		goto out_default;
	error = decode_fattr(xdr, result->fattr, rpc_rqst_userns(req));
	if (unlikely(error))
		goto out;
	error = decode_nfsdata(xdr, result);
out:
	return error;
out_default:
	return nfs_stat_to_errno(status);
}