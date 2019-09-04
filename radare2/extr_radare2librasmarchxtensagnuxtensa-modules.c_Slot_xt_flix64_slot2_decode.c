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
 int Field_combined3e2c5767_fld36xt_flix64_slot2_Slot_xt_flix64_slot2_get (int /*<<< orphan*/  const) ; 
 scalar_t__ Field_combined3e2c5767_fld37xt_flix64_slot2_Slot_xt_flix64_slot2_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld39xt_flix64_slot2_Slot_xt_flix64_slot2_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld41xt_flix64_slot2_Slot_xt_flix64_slot2_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld42xt_flix64_slot2_Slot_xt_flix64_slot2_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld44xt_flix64_slot2_Slot_xt_flix64_slot2_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld45xt_flix64_slot2_Slot_xt_flix64_slot2_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld47xt_flix64_slot2_Slot_xt_flix64_slot2_get (int /*<<< orphan*/  const) ; 
 scalar_t__ Field_combined3e2c5767_fld63xt_flix64_slot2_Slot_xt_flix64_slot2_get (int /*<<< orphan*/  const) ; 
 scalar_t__ Field_combined3e2c5767_fld64xt_flix64_slot2_Slot_xt_flix64_slot2_get (int /*<<< orphan*/  const) ; 
 scalar_t__ Field_combined3e2c5767_fld65xt_flix64_slot2_Slot_xt_flix64_slot2_get (int /*<<< orphan*/  const) ; 
 scalar_t__ Field_combined3e2c5767_fld66xt_flix64_slot2_Slot_xt_flix64_slot2_get (int /*<<< orphan*/  const) ; 
 scalar_t__ Field_combined3e2c5767_fld68xt_flix64_slot2_Slot_xt_flix64_slot2_get (int /*<<< orphan*/  const) ; 
 int Field_op0_s5_Slot_xt_flix64_slot2_get (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
Slot_xt_flix64_slot2_decode (const xtensa_insnbuf insn)
{
  switch (Field_combined3e2c5767_fld36xt_flix64_slot2_Slot_xt_flix64_slot2_get (insn))
    {
    case 0:
	    if (Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 1) {
		    return 41; /* add */
	    }
	    if (Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 5) {
		    return 42; /* sub */
	    }
	    if (Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 2) {
		    return 43; /* addx2 */
	    }
	    if (Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 3) {
		    return 49; /* and */
	    }
	    if (Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 4) {
		    return 450; /* sext */
	    }
	    break;
    case 1:
	    if (Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 1) {
		    return 27; /* addi.n */
	    }
	    if (Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 2) {
		    return 44; /* addx4 */
	    }
	    if (Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 3) {
		    return 50; /* or */
	    }
	    if (Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 5) {
		    return 51; /* xor */
	    }
	    if (Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 4) {
		    return 113; /* srli */
	    }
	    break;
    }
    if (Field_combined3e2c5767_fld37xt_flix64_slot2_Slot_xt_flix64_slot2_get (insn) == 0 &&
	    Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 6) {
	    return 33; /* movi.n */
    }
    if (Field_combined3e2c5767_fld39xt_flix64_slot2_Slot_xt_flix64_slot2_get (insn) == 2 &&
	    Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 6 &&
	    Field_combined3e2c5767_fld63xt_flix64_slot2_Slot_xt_flix64_slot2_get (insn) == 0) {
	    return 32; /* mov.n */
    }
    if (Field_combined3e2c5767_fld41xt_flix64_slot2_Slot_xt_flix64_slot2_get (insn) == 3 &&
	    Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 6 &&
	    Field_combined3e2c5767_fld65xt_flix64_slot2_Slot_xt_flix64_slot2_get (insn) == 0) {
	    return 97; /* nop */
    }
    if (Field_combined3e2c5767_fld42xt_flix64_slot2_Slot_xt_flix64_slot2_get (insn) == 8 &&
	    Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 6 &&
	    Field_combined3e2c5767_fld64xt_flix64_slot2_Slot_xt_flix64_slot2_get (insn) == 0) {
	    return 96; /* abs */
    }
    if (Field_combined3e2c5767_fld44xt_flix64_slot2_Slot_xt_flix64_slot2_get (insn) == 9 &&
	    Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 6 &&
	    Field_combined3e2c5767_fld64xt_flix64_slot2_Slot_xt_flix64_slot2_get (insn) == 0) {
	    return 95; /* neg */
    }
    if (Field_combined3e2c5767_fld45xt_flix64_slot2_Slot_xt_flix64_slot2_get (insn) == 5 &&
	    Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 6 &&
	    Field_combined3e2c5767_fld66xt_flix64_slot2_Slot_xt_flix64_slot2_get (insn) == 0) {
	    return 110; /* sra */
    }
    if (Field_combined3e2c5767_fld47xt_flix64_slot2_Slot_xt_flix64_slot2_get (insn) == 3 &&
	    Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 6 &&
	    Field_combined3e2c5767_fld68xt_flix64_slot2_Slot_xt_flix64_slot2_get (insn) == 0) {
	    return 109; /* srl */
    }
    if (Field_op0_s5_Slot_xt_flix64_slot2_get (insn) == 7) {
	    return 112; /* srai */
    }
    return 0;
}