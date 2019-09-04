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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int fdt_appendprop_u32 (void*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int fdt_appendprop_cell(void *fdt, int nodeoffset,
				      const char *name, uint32_t val)
{
	return fdt_appendprop_u32(fdt, nodeoffset, name, val);
}