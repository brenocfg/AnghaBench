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
typedef  int /*<<< orphan*/  RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  ESIL_A (char*,...) ; 

__attribute__((used)) static void __generic_pop(RAnalOp *op, int sz) {
	if (sz > 1) {
		ESIL_A ("1,sp,+,_ram,+,");	// calc SRAM(sp+1)
		ESIL_A ("[%d],", sz);		// read value
		ESIL_A ("%d,sp,+=,", sz);	// sp += item_size
	} else {
		ESIL_A ("1,sp,+=,"		// increment stack pointer
			"sp,_ram,+,[1],");	// load SRAM[sp]
	}
}