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
typedef  int ut8 ;
struct TYPE_3__ {int jump; int /*<<< orphan*/  esil; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,char*,int) ; 

__attribute__((used)) static void _6502_anal_esil_ccall(RAnalOp *op, ut8 data0) {
	char *flag;
	switch (data0) {
	case 0x10: // bpl $ffff
		flag = "N,!";
		break;
	case 0x30: // bmi $ffff
		flag = "N";
		break;
	case 0x50: // bvc $ffff
		flag = "V,!";
		break;
	case 0x70: // bvs $ffff
		flag = "V";
		break;
	case 0x90: // bcc $ffff
		flag = "C,!";
		break;
	case 0xb0: // bcs $ffff
		flag = "C";
		break;
	case 0xd0: // bne $ffff
		flag = "Z,!";
		break;
	case 0xf0: // beq $ffff
		flag = "Z";
		break;
	default:
		// FIXME: should not happen
		flag = "unk";
		break;
	}
	r_strbuf_setf (&op->esil, "%s,?{,0x%04x,pc,=,}", flag, (op->jump & 0xffff));
}