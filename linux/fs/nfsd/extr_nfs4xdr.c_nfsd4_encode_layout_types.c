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
 unsigned long LAYOUT_NFSV4_1_FILES ; 
 unsigned long LAYOUT_TYPE_MAX ; 
 void* cpu_to_be32 (unsigned long) ; 
 unsigned long hweight_long (int) ; 
 int /*<<< orphan*/  nfserr_resource ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static inline __be32
nfsd4_encode_layout_types(struct xdr_stream *xdr, u32 layout_types)
{
	__be32		*p;
	unsigned long	i = hweight_long(layout_types);

	p = xdr_reserve_space(xdr, 4 + 4 * i);
	if (!p)
		return nfserr_resource;

	*p++ = cpu_to_be32(i);

	for (i = LAYOUT_NFSV4_1_FILES; i < LAYOUT_TYPE_MAX; ++i)
		if (layout_types & (1 << i))
			*p++ = cpu_to_be32(i);

	return 0;
}