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
typedef  int /*<<< orphan*/  fdt32_t ;

/* Variables and functions */
 int FDT_ERR_BADNCELLS ; 
 int FDT_MAX_NCELLS ; 
 int fdt32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * fdt_getprop (void const*,int,char const*,int*) ; 

__attribute__((used)) static int fdt_cells(const void *fdt, int nodeoffset, const char *name)
{
	const fdt32_t *c;
	int val;
	int len;

	c = fdt_getprop(fdt, nodeoffset, name, &len);
	if (!c)
		return len;

	if (len != sizeof(*c))
		return -FDT_ERR_BADNCELLS;

	val = fdt32_to_cpu(*c);
	if ((val <= 0) || (val > FDT_MAX_NCELLS))
		return -FDT_ERR_BADNCELLS;

	return val;
}