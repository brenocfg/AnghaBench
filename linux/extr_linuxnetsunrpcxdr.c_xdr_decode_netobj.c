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
typedef  int /*<<< orphan*/  u8 ;
struct xdr_netobj {unsigned int len; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int XDR_MAX_NETOBJ ; 
 int XDR_QUADLEN (unsigned int) ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 

__be32 *
xdr_decode_netobj(__be32 *p, struct xdr_netobj *obj)
{
	unsigned int	len;

	if ((len = be32_to_cpu(*p++)) > XDR_MAX_NETOBJ)
		return NULL;
	obj->len  = len;
	obj->data = (u8 *) p;
	return p + XDR_QUADLEN(len);
}