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
struct TYPE_3__ {int /*<<< orphan*/  esil; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,int,char) ; 

__attribute__((used)) static void _6502_anal_esil_flags(RAnalOp *op, ut8 data0) {
	int enabled=0;
	char flag ='u';
	switch(data0) {
	case 0x78: // sei
		enabled = 1;
		flag = 'I';
		break;
	case 0x58: // cli
		enabled = 0;
		flag = 'I';
		break;
	case 0x38: // sec
		enabled = 1;
		flag = 'C';
		break;
	case 0x18: // clc
		enabled = 0;
		flag = 'C';
		break;
	case 0xf8: // sed
		enabled = 1;
		flag = 'D';
		break;
	case 0xd8: // cld
		enabled = 0;
		flag = 'D';
		break;
	case 0xb8: // clv
		enabled = 0;
		flag = 'V';
		break;
		break;
	}
	r_strbuf_setf (&op->esil, "%d,%c,=", enabled, flag);
}