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
typedef  size_t ut8 ;
struct TYPE_3__ {int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;
typedef  TYPE_1__ ebc_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBC_INSTR_MAXLEN ; 
 size_t const EBC_OPCODE_MASK ; 
 int /*<<< orphan*/  EBC_OPERANDS_MAXLEN ; 
 char** dedic_regs ; 
 char** instr_names ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,...) ; 

__attribute__((used)) static int decode_loadsp(const ut8 *bytes, ebc_command_t *cmd) {
	int ret = 2;
	snprintf(cmd->instr, EBC_INSTR_MAXLEN, "%s",
			instr_names[bytes[0] & EBC_OPCODE_MASK]);
	snprintf(cmd->operands, EBC_OPERANDS_MAXLEN, "%s, r%u",
			dedic_regs[bytes[1] & 0x7],
			(bytes[1] >> 4) & 0x7);
	return ret;
}