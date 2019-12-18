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
 int fdt_find_max_phandle (void const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint32_t fdt_get_max_phandle(const void *fdt)
{
	uint32_t phandle;
	int err;

	err = fdt_find_max_phandle(fdt, &phandle);
	if (err < 0)
		return (uint32_t)-1;

	return phandle;
}