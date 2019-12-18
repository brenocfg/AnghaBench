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
typedef  int /*<<< orphan*/  ut8 ;
struct v810_cmd {char* instr; char* operands; } ;
struct TYPE_4__ {int size; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  int /*<<< orphan*/  RAsm ;

/* Variables and functions */
 int /*<<< orphan*/  r_asm_op_set_asm (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_fmt (char*,char*,char*) ; 
 int v810_decode_command (int /*<<< orphan*/  const*,int,struct v810_cmd*) ; 

__attribute__((used)) static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	struct v810_cmd cmd = {
		.instr = "",
		.operands = ""
	};
	if (len < 2) {
		return -1;
	}
	int ret = v810_decode_command (buf, len, &cmd);
	if (ret > 0) {
		r_asm_op_set_asm (op, sdb_fmt ("%s %s", cmd.instr, cmd.operands));
	}
	return op->size = ret;
}