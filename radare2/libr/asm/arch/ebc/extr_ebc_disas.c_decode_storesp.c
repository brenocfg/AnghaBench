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
struct TYPE_3__ {int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;
typedef  TYPE_1__ ebc_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHK_SNPRINTF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int const,char*) ; 
 int /*<<< orphan*/  EBC_INSTR_MAXLEN ; 
 int const EBC_OPCODE_MASK ; 
 int /*<<< orphan*/  EBC_OPERANDS_MAXLEN ; 
 char** dedic_regs ; 
 char** instr_names ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int decode_storesp(const ut8 *bytes, ebc_command_t *cmd) {
	int ret = 2;
	unsigned op2 = (bytes[1] >> 4) & 0x07;
	snprintf (cmd->instr, EBC_INSTR_MAXLEN, "%s",
		instr_names[bytes[0] & EBC_OPCODE_MASK]);
	CHK_SNPRINTF (cmd->operands, EBC_OPERANDS_MAXLEN, "r%u, %s",
		bytes[1] & 0x7,
		op2 < 2 ? dedic_regs[op2] : "RESERVED_DEDICATED_REG");
	return ret;
}