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
 void const* fdt_getprop_namelen (void const*,int,char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

const void *fdt_getprop(const void *fdt, int nodeoffset,
			const char *name, int *lenp)
{
	return fdt_getprop_namelen(fdt, nodeoffset, name, strlen(name), lenp);
}