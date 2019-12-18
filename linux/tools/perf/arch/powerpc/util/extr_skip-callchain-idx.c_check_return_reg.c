#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ atom; scalar_t__ number2; scalar_t__ offset; int number; } ;
typedef  TYPE_1__ Dwarf_Op ;
typedef  int /*<<< orphan*/  Dwarf_Frame ;

/* Variables and functions */
 scalar_t__ DW_OP_bregx ; 
 scalar_t__ DW_OP_regx ; 
 int /*<<< orphan*/  dwarf_errmsg (int) ; 
 int dwarf_frame_cfa (int /*<<< orphan*/ *,TYPE_1__**,size_t*) ; 
 int dwarf_frame_register (int /*<<< orphan*/ *,int,TYPE_1__*,TYPE_1__**,size_t*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 

__attribute__((used)) static int check_return_reg(int ra_regno, Dwarf_Frame *frame)
{
	Dwarf_Op ops_mem[2];
	Dwarf_Op dummy;
	Dwarf_Op *ops = &dummy;
	size_t nops;
	int result;

	result = dwarf_frame_register(frame, ra_regno, ops_mem, &ops, &nops);
	if (result < 0) {
		pr_debug("dwarf_frame_register() %s\n", dwarf_errmsg(-1));
		return -1;
	}

	/*
	 * Check if return address is on the stack. If return address
	 * is in a register (typically R0), it is yet to be saved on
	 * the stack.
	 */
	if ((nops != 0 || ops != NULL) &&
		!(nops == 1 && ops[0].atom == DW_OP_regx &&
			ops[0].number2 == 0 && ops[0].offset == 0))
		return 0;

	/*
	 * Return address is in LR. Check if a frame was allocated
	 * but not-yet used.
	 */
	result = dwarf_frame_cfa(frame, &ops, &nops);
	if (result < 0) {
		pr_debug("dwarf_frame_cfa() returns %d, %s\n", result,
					dwarf_errmsg(-1));
		return -1;
	}

	/*
	 * If call frame address is in r1, no new frame was allocated.
	 */
	if (nops == 1 && ops[0].atom == DW_OP_bregx && ops[0].number == 1 &&
				ops[0].number2 == 0)
		return 1;

	/*
	 * A new frame was allocated but has not yet been used.
	 */
	return 2;
}