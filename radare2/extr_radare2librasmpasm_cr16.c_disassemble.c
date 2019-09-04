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
typedef  int /*<<< orphan*/  ut8 ;
struct cr16_cmd {int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;
struct TYPE_3__ {int size; int /*<<< orphan*/  buf_asm; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  int /*<<< orphan*/  RAsm ;

/* Variables and functions */
 int cr16_decode_command (int /*<<< orphan*/  const*,struct cr16_cmd*) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_fmt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	struct cr16_cmd cmd;
	int ret = cr16_decode_command (buf, &cmd);
	r_strbuf_set (&op->buf_asm, sdb_fmt ("%s %s", cmd.instr, cmd.operands));
	return op->size = ret;
}