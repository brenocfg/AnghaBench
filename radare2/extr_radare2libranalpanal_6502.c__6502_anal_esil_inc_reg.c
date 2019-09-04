#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_4__ {int /*<<< orphan*/  esil; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  _6502_FLAGS_NZ ; 
 int /*<<< orphan*/  _6502_anal_update_flags (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,char*,char*,char*) ; 

__attribute__((used)) static void _6502_anal_esil_inc_reg(RAnalOp *op, ut8 data0, char* sign) {
	char* reg = NULL;

	switch(data0) {
	case 0xe8: // inx
	case 0xca: // dex
		reg = "x";
		break;
	case 0xc8: // iny
	case 0x88: // dey
		reg = "y";
		break;
	}
	r_strbuf_setf (&op->esil, "%s,%s%s=", reg, sign, sign);
	_6502_anal_update_flags (op, _6502_FLAGS_NZ);
}