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
 int /*<<< orphan*/  FDT_CHECK_HEADER (void*) ; 
 int /*<<< orphan*/  fdt_get_max_phandle (void*) ; 
 int /*<<< orphan*/  fdt_set_magic (void*,int /*<<< orphan*/ ) ; 
 int overlay_adjust_local_phandles (void*,int /*<<< orphan*/ ) ; 
 int overlay_fixup_phandles (void*,void*) ; 
 int overlay_merge (void*,void*) ; 
 int overlay_symbol_update (void*,void*) ; 
 int overlay_update_local_references (void*,int /*<<< orphan*/ ) ; 

int fdt_overlay_apply(void *fdt, void *fdto)
{
	uint32_t delta = fdt_get_max_phandle(fdt);
	int ret;

	FDT_CHECK_HEADER(fdt);
	FDT_CHECK_HEADER(fdto);

	ret = overlay_adjust_local_phandles(fdto, delta);
	if (ret)
		goto err;

	ret = overlay_update_local_references(fdto, delta);
	if (ret)
		goto err;

	ret = overlay_fixup_phandles(fdt, fdto);
	if (ret)
		goto err;

	ret = overlay_merge(fdt, fdto);
	if (ret)
		goto err;

	ret = overlay_symbol_update(fdt, fdto);
	if (ret)
		goto err;

	/*
	 * The overlay has been damaged, erase its magic.
	 */
	fdt_set_magic(fdto, ~0);

	return 0;

err:
	/*
	 * The overlay might have been damaged, erase its magic.
	 */
	fdt_set_magic(fdto, ~0);

	/*
	 * The base device tree might have been damaged, erase its
	 * magic.
	 */
	fdt_set_magic(fdt, ~0);

	return ret;
}