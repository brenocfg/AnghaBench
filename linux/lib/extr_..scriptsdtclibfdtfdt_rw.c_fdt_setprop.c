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

/* Variables and functions */
 int fdt_setprop_placeholder (void*,int,char const*,int,void**) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 

int fdt_setprop(void *fdt, int nodeoffset, const char *name,
		const void *val, int len)
{
	void *prop_data;
	int err;

	err = fdt_setprop_placeholder(fdt, nodeoffset, name, len, &prop_data);
	if (err)
		return err;

	if (len)
		memcpy(prop_data, val, len);
	return 0;
}