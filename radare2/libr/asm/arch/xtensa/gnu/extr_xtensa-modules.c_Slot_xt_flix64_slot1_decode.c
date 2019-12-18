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
typedef  int /*<<< orphan*/  xtensa_insnbuf ;

/* Variables and functions */
 int /*<<< orphan*/  Field_combined3e2c5767_fld16_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 scalar_t__ Field_combined3e2c5767_fld19xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld20xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld21xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld22xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld23xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld25xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld26xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld28xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld30xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld32xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld33xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld35xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 scalar_t__ Field_combined3e2c5767_fld51xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 scalar_t__ Field_combined3e2c5767_fld52xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 scalar_t__ Field_combined3e2c5767_fld53xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 scalar_t__ Field_combined3e2c5767_fld54xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld57xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 scalar_t__ Field_combined3e2c5767_fld58xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 scalar_t__ Field_combined3e2c5767_fld60xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 scalar_t__ Field_combined3e2c5767_fld62xt_flix64_slot1_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 
 int Field_op0_s4_Slot_xt_flix64_slot1_get (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
Slot_xt_flix64_slot1_decode (const xtensa_insnbuf insn)
{
	if (Field_combined3e2c5767_fld19xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 0 &&
		Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 1) {
		return 78; /* extui */
	}
	switch (Field_combined3e2c5767_fld20xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn)) {
	case 0:
		if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
			return 90; /* movi */
		}
		break;
	case 2:
		if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 1) {
			return 39; /* addi */
		}
		break;
	case 3:
		if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 1) {
			return 40; /* addmi */
		}
		if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2 &&
			Field_combined3e2c5767_fld16_Slot_xt_flix64_slot1_get (insn) == 0) {
			return 51; /* xor */
		}
		break;
    }
  switch (Field_combined3e2c5767_fld21xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn))
    {
    case 8:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 111; /* slli */
	    }
	    break;
    case 16:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 112; /* srai */
	    }
	    break;
    case 19:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2 &&
		    Field_combined3e2c5767_fld57xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 0) {
		    return 107; /* sll */
	    }
	    break;
    }
  switch (Field_combined3e2c5767_fld22xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn))
    {
    case 18:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 41; /* add */
	    }
	    break;
    case 19:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 45; /* addx8 */
	    }
	    break;
    case 20:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 43; /* addx2 */
	    }
	    break;
    case 21:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 49; /* and */
	    }
	    break;
    case 22:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 91; /* moveqz */
	    }
	    break;
    case 23:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 94; /* movgez */
	    }
	    break;
    case 24:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 44; /* addx4 */
	    }
	    break;
    case 25:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 93; /* movltz */
	    }
	    break;
    case 26:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 92; /* movnez */
	    }
	    break;
    case 27:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 296; /* mul16u */
	    }
	    break;
    case 28:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 297; /* mul16s */
	    }
	    break;
    case 29:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 461; /* mull */
	    }
	    break;
    case 30:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 50; /* or */
	    }
	    break;
    case 31:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 450; /* sext */
	    }
	    break;
    case 34:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 108; /* src */
	    }
	    break;
    case 36:
	    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2) {
		    return 113; /* srli */
	    }
	    break;
    }
    if (Field_combined3e2c5767_fld23xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 280 &&
	    Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2 &&
	    Field_combined3e2c5767_fld51xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 0) {
	    return 32; /* mov.n */
    }
    if (Field_combined3e2c5767_fld25xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 281 &&
	    Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2 &&
	    Field_combined3e2c5767_fld52xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 0) {
	    return 81; /* jx */
    }
    if (Field_combined3e2c5767_fld26xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 141 &&
	    Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2 &&
	    Field_combined3e2c5767_fld60xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 0) {
	    return 103; /* ssl */
    }
    if (Field_combined3e2c5767_fld28xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 71 &&
	    Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2 &&
	    Field_combined3e2c5767_fld54xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 0) {
	    return 97; /* nop */
    }
    if (Field_combined3e2c5767_fld30xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 148 &&
	    Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2 &&
	    Field_combined3e2c5767_fld53xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 0) {
	    return 95; /* neg */
    }
    if (Field_combined3e2c5767_fld32xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 149 &&
	    Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2 &&
	    Field_combined3e2c5767_fld53xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 0) {
	    return 110; /* sra */
    }
    if (Field_combined3e2c5767_fld33xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 75 &&
	    Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2 &&
	    Field_combined3e2c5767_fld58xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 0) {
	    return 109; /* srl */
    }
    if (Field_combined3e2c5767_fld35xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 5 &&
	    Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 2 &&
	    Field_combined3e2c5767_fld62xt_flix64_slot1_Slot_xt_flix64_slot1_get (insn) == 0) {
	    return 42; /* sub */
    }
    if (Field_op0_s4_Slot_xt_flix64_slot1_get (insn) == 3) {
	    return 80; /* j */
    }
    return 0;
}