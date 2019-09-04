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
 int /*<<< orphan*/  Field_combined3e2c5767_fld70xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld71_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld72xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld73xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld74xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld75xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld76xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld77xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld78xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld79xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld80xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld81xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld82xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld83xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld84xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld85xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld86xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld87xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld88xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld89xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld90xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld91xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld92xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_combined3e2c5767_fld93xt_flix64_slot3_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 
 int Field_op0_s6_Slot_xt_flix64_slot3_get (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
Slot_xt_flix64_slot3_decode (const xtensa_insnbuf insn)
{
  switch (Field_op0_s6_Slot_xt_flix64_slot3_get (insn))
    {
    case 1:
	    if (Field_combined3e2c5767_fld71_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 516; /* bbci.w18 */
	    }
	    break;
    case 2:
	    if (Field_combined3e2c5767_fld71_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 517; /* bbsi.w18 */
	    }
	    break;
    case 3:
	    if (Field_combined3e2c5767_fld89xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 526; /* ball.w18 */
	    }
	    break;
    case 4:
	    if (Field_combined3e2c5767_fld87xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 524; /* bany.w18 */
	    }
	    break;
    case 5:
	    if (Field_combined3e2c5767_fld91xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 528; /* bbc.w18 */
	    }
	    break;
    case 6:
	    if (Field_combined3e2c5767_fld92xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 529; /* bbs.w18 */
	    }
	    break;
    case 7:
	    if (Field_combined3e2c5767_fld81xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 518; /* beq.w18 */
	    }
	    break;
    case 8:
	    if (Field_combined3e2c5767_fld75xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 510; /* beqi.w18 */
	    }
	    break;
    case 9:
	    if (Field_combined3e2c5767_fld83xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 520; /* bge.w18 */
	    }
	    break;
    case 10:
	    if (Field_combined3e2c5767_fld77xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 512; /* bgei.w18 */
	    }
	    break;
    case 11:
	    if (Field_combined3e2c5767_fld85xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 522; /* bgeu.w18 */
	    }
	    break;
    case 12:
	    if (Field_combined3e2c5767_fld79xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 514; /* bgeui.w18 */
	    }
	    break;
    case 13:
	    if (Field_combined3e2c5767_fld84xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 521; /* blt.w18 */
	    }
	    break;
    case 14:
	    if (Field_combined3e2c5767_fld78xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 513; /* blti.w18 */
	    }
	    break;
    case 15:
	    if (Field_combined3e2c5767_fld86xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 523; /* bltu.w18 */
	    }
	    break;
    case 16:
	    if (Field_combined3e2c5767_fld80xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 515; /* bltui.w18 */
	    }
	    break;
    case 17:
	    if (Field_combined3e2c5767_fld90xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 527; /* bnall.w18 */
	    }
	    break;
    case 18:
	    if (Field_combined3e2c5767_fld82xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 519; /* bne.w18 */
	    }
	    break;
    case 19:
	    if (Field_combined3e2c5767_fld76xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 511; /* bnei.w18 */
	    }
	    break;
    case 20:
	    if (Field_combined3e2c5767_fld88xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 525; /* bnone.w18 */
	    }
	    break;
    case 21:
	    if (Field_combined3e2c5767_fld70xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 506; /* beqz.w18 */
	    }
	    break;
    case 22:
	    if (Field_combined3e2c5767_fld73xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 508; /* bgez.w18 */
	    }
	    break;
    case 23:
	    if (Field_combined3e2c5767_fld74xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 509; /* bltz.w18 */
	    }
	    break;
    case 24:
	    if (Field_combined3e2c5767_fld72xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 507; /* bnez.w18 */
	    }
	    break;
    case 25:
	    if (Field_combined3e2c5767_fld93xt_flix64_slot3_Slot_xt_flix64_slot3_get (insn) == 0) {
		    return 97; /* nop */
	    }
	    break;
    }
  return 0;
}