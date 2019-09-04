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
struct TYPE_3__ {size_t length; int /*<<< orphan*/ * attr_values; } ;
typedef  TYPE_1__ RBinDwarfDIE ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_bin_dwarf_free_attr_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r_bin_dwarf_free_die(RBinDwarfDIE *die) {
	size_t i;
	if (!die) {
		return;
	}
	for (i = 0; i < die->length; i++) {
		r_bin_dwarf_free_attr_value (&die->attr_values[i]);
	}
	R_FREE (die->attr_values);
}