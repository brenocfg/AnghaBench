#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t length; int /*<<< orphan*/ * comp_units; } ;
typedef  TYPE_1__ RBinDwarfDebugInfo ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_bin_dwarf_free_comp_unit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r_bin_dwarf_free_debug_info(RBinDwarfDebugInfo *inf) {
	size_t i;
	if (!inf) {
		return;
	}
	for (i = 0; i < inf->length; i++) {
		r_bin_dwarf_free_comp_unit (&inf->comp_units[i]);
	}
	R_FREE (inf->comp_units);
}