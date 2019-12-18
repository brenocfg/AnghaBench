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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/ * xdr_encode_opaque_fixed (int /*<<< orphan*/ *,void const*,unsigned int) ; 

__be32 *xdr_encode_opaque(__be32 *p, const void *ptr, unsigned int nbytes)
{
	*p++ = cpu_to_be32(nbytes);
	return xdr_encode_opaque_fixed(p, ptr, nbytes);
}