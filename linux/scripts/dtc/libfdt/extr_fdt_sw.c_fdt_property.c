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
 int fdt_property_placeholder (void*,char const*,int,void**) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 

int fdt_property(void *fdt, const char *name, const void *val, int len)
{
	void *ptr;
	int ret;

	ret = fdt_property_placeholder(fdt, name, len, &ptr);
	if (ret)
		return ret;
	memcpy(ptr, val, len);
	return 0;
}