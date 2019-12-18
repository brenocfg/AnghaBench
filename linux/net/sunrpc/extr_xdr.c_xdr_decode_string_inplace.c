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
typedef  unsigned int u32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int XDR_QUADLEN (unsigned int) ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 

__be32 *
xdr_decode_string_inplace(__be32 *p, char **sp,
			  unsigned int *lenp, unsigned int maxlen)
{
	u32 len;

	len = be32_to_cpu(*p++);
	if (len > maxlen)
		return NULL;
	*lenp = len;
	*sp = (char *) p;
	return p + XDR_QUADLEN(len);
}