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
struct TYPE_3__ {scalar_t__ length; int /*<<< orphan*/  capacity; int /*<<< orphan*/  dies; } ;
typedef  int /*<<< orphan*/  RBinDwarfDIE ;
typedef  TYPE_1__ RBinDwarfCompUnit ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_UNIT_CAPACITY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  calloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_bin_dwarf_init_comp_unit(RBinDwarfCompUnit *cu) {
	if (!cu) {
		return -EINVAL;
	}
	cu->dies = calloc (sizeof (RBinDwarfDIE), COMP_UNIT_CAPACITY);
	if (!cu->dies) {
		return -ENOMEM;
	}
	cu->capacity = COMP_UNIT_CAPACITY;
	cu->length = 0;
	return 0;
}