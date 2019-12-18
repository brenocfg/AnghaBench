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

/* Variables and functions */
 int FDT_ERR_NOSPACE ; 
 void* fdt_getprop_namelen_w (void*,int,char const*,int,int*) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,int) ; 

int fdt_setprop_inplace_namelen_partial(void *fdt, int nodeoffset,
					const char *name, int namelen,
					uint32_t idx, const void *val,
					int len)
{
	void *propval;
	int proplen;

	propval = fdt_getprop_namelen_w(fdt, nodeoffset, name, namelen,
					&proplen);
	if (!propval)
		return proplen;

	if (proplen < (len + idx))
		return -FDT_ERR_NOSPACE;

	memcpy((char *)propval + idx, val, len);
	return 0;
}