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
struct nfs42_copy_res {void* synchronous; void* consecutive; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 void* be32_to_cpup (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_copy_requirements(struct xdr_stream *xdr,
				    struct nfs42_copy_res *res) {
	__be32 *p;

	p = xdr_inline_decode(xdr, 4 + 4);
	if (unlikely(!p))
		return -EIO;

	res->consecutive = be32_to_cpup(p++);
	res->synchronous = be32_to_cpup(p++);
	return 0;
}