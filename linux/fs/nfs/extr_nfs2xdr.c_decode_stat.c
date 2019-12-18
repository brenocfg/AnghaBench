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
typedef  enum nfs_stat { ____Placeholder_nfs_stat } nfs_stat ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NFS_OK ; 
 int be32_to_cpup (scalar_t__*) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_nfs_xdr_status (struct xdr_stream*,int) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__* xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_stat(struct xdr_stream *xdr, enum nfs_stat *status)
{
	__be32 *p;

	p = xdr_inline_decode(xdr, 4);
	if (unlikely(!p))
		return -EIO;
	if (unlikely(*p != cpu_to_be32(NFS_OK)))
		goto out_status;
	*status = 0;
	return 0;
out_status:
	*status = be32_to_cpup(p);
	trace_nfs_xdr_status(xdr, (int)*status);
	return 0;
}