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
struct TYPE_3__ {scalar_t__ length; int /*<<< orphan*/  capacity; int /*<<< orphan*/  comp_units; } ;
typedef  TYPE_1__ RBinDwarfDebugInfo ;
typedef  int /*<<< orphan*/  RBinDwarfCompUnit ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_INFO_CAPACITY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  calloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_bin_dwarf_init_debug_info(RBinDwarfDebugInfo *inf) {
	if (!inf) {
		return -1;
	}
	inf->comp_units = calloc (sizeof (RBinDwarfCompUnit), DEBUG_INFO_CAPACITY);

	// XXX - should we be using error codes?
	if (!inf->comp_units) {
		return -ENOMEM;
	}

	inf->capacity = DEBUG_INFO_CAPACITY;
	inf->length = 0;

	return true;
}