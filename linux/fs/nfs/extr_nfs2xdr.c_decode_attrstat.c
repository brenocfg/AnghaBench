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
struct user_namespace {int dummy; } ;
struct nfs_fattr {int dummy; } ;
typedef  enum nfs_stat { ____Placeholder_nfs_stat } nfs_stat ;
typedef  int __u32 ;

/* Variables and functions */
 int NFS_OK ; 
 int decode_fattr (struct xdr_stream*,struct nfs_fattr*,struct user_namespace*) ; 
 int decode_stat (struct xdr_stream*,int*) ; 
 int nfs_stat_to_errno (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int decode_attrstat(struct xdr_stream *xdr, struct nfs_fattr *result,
			   __u32 *op_status,
			   struct user_namespace *userns)
{
	enum nfs_stat status;
	int error;

	error = decode_stat(xdr, &status);
	if (unlikely(error))
		goto out;
	if (op_status)
		*op_status = status;
	if (status != NFS_OK)
		goto out_default;
	error = decode_fattr(xdr, result, userns);
out:
	return error;
out_default:
	return nfs_stat_to_errno(status);
}