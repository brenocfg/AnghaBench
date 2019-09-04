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
 int /*<<< orphan*/  CONFIG_CPU_BIG_ENDIAN ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ fdt_getprop (void const*,unsigned long,char*,int /*<<< orphan*/ *) ; 

bool of_fdt_is_big_endian(const void *blob, unsigned long node)
{
	if (fdt_getprop(blob, node, "big-endian", NULL))
		return true;
	if (IS_ENABLED(CONFIG_CPU_BIG_ENDIAN) &&
	    fdt_getprop(blob, node, "native-endian", NULL))
		return true;
	return false;
}