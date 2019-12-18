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

__attribute__((used)) static void __generic_ld_st(RAnalOp *op, char *mem, char ireg, int use_ramp, int prepostdec, int offset, int st) {
	if (ireg) {
		// preincrement index register
		if (prepostdec < 0) {
			ESIL_A ("1,%c,-,%c,=,", ireg, ireg);
		}
		// set register index address
		ESIL_A ("%c,", ireg);
		// add offset
		if (offset != 0) {
			ESIL_A ("%d,+,", offset);
		}
	} else {
		ESIL_A ("%d,", offset);
	}
	if (use_ramp) {
		ESIL_A ("16,ramp%c,<<,+,", ireg ? ireg : 'd');
	}
	// set SRAM base address
	ESIL_A ("_%s,+,", mem);
	// read/write from SRAM
	ESIL_A ("%s[1],", st ? "=" : "");
	// postincrement index register
	if (ireg && prepostdec > 0) {
		ESIL_A ("1,%c,+,%c,=,", ireg, ireg);
	}
}