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

__attribute__((used)) static void __generic_push(RAnalOp *op, int sz) {
	ESIL_A ("sp,_ram,+,");			// calc pointer SRAM(sp)
	if (sz > 1) {
		ESIL_A ("-%d,+,", sz - 1);	// dec SP by 'sz'
	}
	ESIL_A ("=[%d],", sz);			// store value in stack
	ESIL_A ("-%d,sp,+=,", sz);		// decrement stack pointer
}