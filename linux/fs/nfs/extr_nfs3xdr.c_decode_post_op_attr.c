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
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int EIO ; 
 int decode_fattr3 (struct xdr_stream*,struct nfs_fattr*,struct user_namespace*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__* xdr_inline_decode (struct xdr_stream*,int) ; 
 scalar_t__ xdr_zero ; 

__attribute__((used)) static int decode_post_op_attr(struct xdr_stream *xdr, struct nfs_fattr *fattr,
		struct user_namespace *userns)
{
	__be32 *p;

	p = xdr_inline_decode(xdr, 4);
	if (unlikely(!p))
		return -EIO;
	if (*p != xdr_zero)
		return decode_fattr3(xdr, fattr, userns);
	return 0;
}