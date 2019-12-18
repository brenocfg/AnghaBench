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
typedef  int uint32_t ;
struct xdr_stream {int dummy; } ;
struct nfs_openres {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
#define  WND4_CONTENTION 129 
#define  WND4_RESOURCE 128 
 int be32_to_cpup (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_no_delegation(struct xdr_stream *xdr, struct nfs_openres *res)
{
	__be32 *p;
	uint32_t why_no_delegation;

	p = xdr_inline_decode(xdr, 4);
	if (unlikely(!p))
		return -EIO;
	why_no_delegation = be32_to_cpup(p);
	switch (why_no_delegation) {
		case WND4_CONTENTION:
		case WND4_RESOURCE:
			xdr_inline_decode(xdr, 4);
			/* Ignore for now */
	}
	return 0;
}