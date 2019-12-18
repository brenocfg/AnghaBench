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
struct TYPE_3__ {size_t length; int /*<<< orphan*/ * dies; } ;
typedef  TYPE_1__ RBinDwarfCompUnit ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_bin_dwarf_free_die (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r_bin_dwarf_free_comp_unit(RBinDwarfCompUnit *cu) {
	size_t i;
	if (!cu) {
		return;
	}
	for (i = 0; i < cu->length; i++) {
		if (cu->dies) {
			r_bin_dwarf_free_die (&cu->dies[i]);
		}
	}
	R_FREE (cu->dies);
}