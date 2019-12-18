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
typedef  enum nfs_stat { ____Placeholder_nfs_stat } nfs_stat ;

/* Variables and functions */
 int NFS_OK ; 
 int decode_info (struct xdr_stream*,void*) ; 
 int decode_stat (struct xdr_stream*,int*) ; 
 int nfs_stat_to_errno (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nfs2_xdr_dec_statfsres(struct rpc_rqst *req, struct xdr_stream *xdr,
				  void *result)
{
	enum nfs_stat status;
	int error;

	error = decode_stat(xdr, &status);
	if (unlikely(error))
		goto out;
	if (status != NFS_OK)
		goto out_default;
	error = decode_info(xdr, result);
out:
	return error;
out_default:
	return nfs_stat_to_errno(status);
}