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
struct nfs_fh {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int EIO ; 
 int decode_nfs_fh3 (struct xdr_stream*,struct nfs_fh*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__* xdr_inline_decode (struct xdr_stream*,int) ; 
 scalar_t__ xdr_zero ; 
 int /*<<< orphan*/  zero_nfs_fh3 (struct nfs_fh*) ; 

__attribute__((used)) static int decode_post_op_fh3(struct xdr_stream *xdr, struct nfs_fh *fh)
{
	__be32 *p = xdr_inline_decode(xdr, 4);
	if (unlikely(!p))
		return -EIO;
	if (*p != xdr_zero)
		return decode_nfs_fh3(xdr, fh);
	zero_nfs_fh3(fh);
	return 0;
}