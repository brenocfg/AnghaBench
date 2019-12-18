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
 int Field_combined3e2c5767_fld11_Slot_xt_flix64_slot0_get (int /*<<< orphan*/  const) ; 
 scalar_t__ Field_combined3e2c5767_fld49xt_flix64_slot0_Slot_xt_flix64_slot0_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld7_Slot_xt_flix64_slot0_get (int /*<<< orphan*/  const) ; 
 int Field_combined3e2c5767_fld8_Slot_xt_flix64_slot0_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld9_Slot_xt_flix64_slot0_get (int /*<<< orphan*/  const) ; 
 int Field_op0_xt_flix64_slot0_Slot_xt_flix64_slot0_get (int /*<<< orphan*/  const) ; 
 int Field_op0_xt_flix64_slot0_s3_Slot_xt_flix64_slot0_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_op1_Slot_xt_flix64_slot0_get (int /*<<< orphan*/  const) ; 
 int Field_op2_Slot_xt_flix64_slot0_get (int /*<<< orphan*/  const) ; 
 int Field_r_Slot_xt_flix64_slot0_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_s_Slot_xt_flix64_slot0_get (int /*<<< orphan*/  const) ; 
 scalar_t__ Field_sae4_Slot_xt_flix64_slot0_get (int /*<<< orphan*/  const) ; 
 int Field_t_Slot_xt_flix64_slot0_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_thi3_Slot_xt_flix64_slot0_get (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
Slot_xt_flix64_slot0_decode (const xtensa_insnbuf insn)
{
  switch (Field_op0_xt_flix64_slot0_Slot_xt_flix64_slot0_get (insn))
    {
    case 0:
	    if (Field_combined3e2c5767_fld7_Slot_xt_flix64_slot0_get (insn) == 2) {
		    return 78; /* extui */
	    }
	    switch (Field_op1_Slot_xt_flix64_slot0_get (insn)) {
	    case 0:
		    switch (Field_op2_Slot_xt_flix64_slot0_get (insn)) {
		    case 0:
			    if (Field_r_Slot_xt_flix64_slot0_get (insn) == 2) {
				    if (Field_s_Slot_xt_flix64_slot0_get (insn) == 0) {
					    if (Field_t_Slot_xt_flix64_slot0_get (insn) == 15) {
						    return 97; /* nop */
					    }
				    }
			    }
			    break;
		    case 1:
			    return 49; /* and */
		    case 2:
			    return 50; /* or */
		    case 3:
			    return 51; /* xor */
		    case 4:
			    switch (Field_r_Slot_xt_flix64_slot0_get (insn)) {
			    case 0:
				    if (Field_t_Slot_xt_flix64_slot0_get (insn) == 0) {
					    return 102; /* ssr */
				    }
				    break;
			    case 1:
				    if (Field_t_Slot_xt_flix64_slot0_get (insn) == 0) {
					    return 103; /* ssl */
				    }
				    break;
			    case 2:
				    if (Field_t_Slot_xt_flix64_slot0_get (insn) == 0) {
					    return 104; /* ssa8l */
				    }
				    break;
			    case 3:
				    if (Field_t_Slot_xt_flix64_slot0_get (insn) == 0) {
					    return 105; /* ssa8b */
				    }
				    break;
			    case 4:
				    if (Field_thi3_Slot_xt_flix64_slot0_get (insn) == 0) {
					    return 106; /* ssai */
				    }
				    break;
			    case 14:
				    return 448; /* nsa */
			    case 15:
				    return 449; /* nsau */
			    }
			    break;
		    case 6:
			    switch (Field_s_Slot_xt_flix64_slot0_get (insn)) {
			    case 0:
				    return 95; /* neg */
			    case 1:
				    return 96; /* abs */
			    }
			    break;
		    case 8:
			    return 41; /* add */
		    case 9:
			    return 43; /* addx2 */
		    case 10:
			    return 44; /* addx4 */
		    case 11:
			    return 45; /* addx8 */
		    case 12:
			    return 42; /* sub */
		    case 13:
			    return 46; /* subx2 */
		    case 14:
			    return 47; /* subx4 */
		    case 15:
			    return 48; /* subx8 */
		    }
		    break;
	    case 1:
		    if (Field_combined3e2c5767_fld11_Slot_xt_flix64_slot0_get (insn) == 1) {
			    return 112; /* srai */
		    }
		    if (Field_combined3e2c5767_fld9_Slot_xt_flix64_slot0_get (insn) == 0) {
			    return 111; /* slli */
		    }
		    switch (Field_op2_Slot_xt_flix64_slot0_get (insn)) {
		    case 4:
			    return 113; /* srli */
		    case 8:
			    return 108; /* src */
		    case 9:
			    if (Field_s_Slot_xt_flix64_slot0_get (insn) == 0) {
				    return 109; /* srl */
			    }
			    break;
		    case 10:
			    if (Field_t_Slot_xt_flix64_slot0_get (insn) == 0) {
				    return 107; /* sll */
			    }
			    break;
		    case 11:
			    if (Field_s_Slot_xt_flix64_slot0_get (insn) == 0) {
				    return 110; /* sra */
			    }
			    break;
		    case 12:
			    return 296; /* mul16u */
		    case 13:
			    return 297; /* mul16s */
		    }
		    break;
	    case 2:
		    if (Field_op2_Slot_xt_flix64_slot0_get (insn) == 8) {
			    return 461; /* mull */
		    }
		    break;
	    case 3:
		    switch (Field_op2_Slot_xt_flix64_slot0_get (insn)) {
		    case 2:
			    return 450; /* sext */
		    case 3:
			    return 443; /* clamps */
		    case 4:
			    return 444; /* min */
		    case 5:
			    return 445; /* max */
		    case 6:
			    return 446; /* minu */
		    case 7:
			    return 447; /* maxu */
		    case 8:
			    return 91; /* moveqz */
		    case 9:
			    return 92; /* movnez */
		    case 10:
			    return 93; /* movltz */
		    case 11:
			    return 94; /* movgez */
		    }
		    break;
	}
      break;
    case 2:
      switch (Field_r_Slot_xt_flix64_slot0_get (insn))
	{
	case 0:
	  return 86; /* l8ui */
	case 1:
	  return 82; /* l16ui */
	case 2:
	  return 84; /* l32i */
	case 4:
	  return 101; /* s8i */
	case 5:
	  return 99; /* s16i */
	case 6:
	  return 100; /* s32i */
	case 9:
	  return 83; /* l16si */
	case 10:
	  return 90; /* movi */
	case 12:
	  return 39; /* addi */
	case 13:
	  return 40; /* addmi */
	}
      break;
    }
    if (Field_op0_xt_flix64_slot0_s3_Slot_xt_flix64_slot0_get (insn) == 1) {
	    return 85; /* l32r */
    }
    if (Field_sae4_Slot_xt_flix64_slot0_get (insn) == 0 &&
	    Field_combined3e2c5767_fld8_Slot_xt_flix64_slot0_get (insn) == 3 &&
	    Field_op0_xt_flix64_slot0_s3_Slot_xt_flix64_slot0_get (insn) == 0 &&
	    Field_combined3e2c5767_fld49xt_flix64_slot0_Slot_xt_flix64_slot0_get (insn) == 0) {
	    return 32; /* mov.n */
    }
    return 0;
}