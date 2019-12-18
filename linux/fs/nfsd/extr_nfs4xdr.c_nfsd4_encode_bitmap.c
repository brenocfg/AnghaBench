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
typedef  int u32 ;
struct xdr_stream {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  nfserr_resource ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static __be32
nfsd4_encode_bitmap(struct xdr_stream *xdr, u32 bmval0, u32 bmval1, u32 bmval2)
{
	__be32 *p;

	if (bmval2) {
		p = xdr_reserve_space(xdr, 16);
		if (!p)
			goto out_resource;
		*p++ = cpu_to_be32(3);
		*p++ = cpu_to_be32(bmval0);
		*p++ = cpu_to_be32(bmval1);
		*p++ = cpu_to_be32(bmval2);
	} else if (bmval1) {
		p = xdr_reserve_space(xdr, 12);
		if (!p)
			goto out_resource;
		*p++ = cpu_to_be32(2);
		*p++ = cpu_to_be32(bmval0);
		*p++ = cpu_to_be32(bmval1);
	} else {
		p = xdr_reserve_space(xdr, 8);
		if (!p)
			goto out_resource;
		*p++ = cpu_to_be32(1);
		*p++ = cpu_to_be32(bmval0);
	}

	return 0;
out_resource:
	return nfserr_resource;
}