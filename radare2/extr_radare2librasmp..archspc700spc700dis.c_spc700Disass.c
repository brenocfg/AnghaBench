#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ut8 ;
struct TYPE_2__ {int type; char* name; } ;
typedef  int /*<<< orphan*/  RAsmOp ;

/* Variables and functions */
#define  SPC_ARG16 131 
#define  SPC_ARG8_1 130 
#define  SPC_ARG8_2 129 
#define  SPC_OP 128 
 int /*<<< orphan*/  r_asm_op_set_asm (int /*<<< orphan*/ *,char const*) ; 
 char* sdb_fmt (char*,size_t const,...) ; 
 int spc700OpLength (int) ; 
 TYPE_1__* spc_op_table ; 

__attribute__((used)) static int spc700Disass(RAsmOp *op, const ut8 *buf, int len) {
	int foo = spc700OpLength (spc_op_table[buf[0]].type);
	if (len < foo) {
		return 0;
	}
	const char *buf_asm = "invalid";
	switch (spc_op_table[buf[0]].type) {
	case SPC_OP:
		buf_asm = spc_op_table[buf[0]].name;
		break;
	case SPC_ARG8_1:
		buf_asm = sdb_fmt (spc_op_table[buf[0]].name, buf[1]);
		break;
	case SPC_ARG8_2:
		buf_asm = sdb_fmt (spc_op_table[buf[0]].name, buf[1], buf[2]);
		break;
	case SPC_ARG16:
		buf_asm = sdb_fmt (spc_op_table[buf[0]].name, buf[1]+0x100*buf[2]);
		break;
	}
	r_asm_op_set_asm (op, buf_asm);
	return foo;
}