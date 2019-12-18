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
typedef  size_t ut8 ;
struct TYPE_4__ {int /*<<< orphan*/  instr; } ;
typedef  TYPE_1__ ebc_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBC_INSTR_MAXLEN ; 
 size_t const EBC_OPCODE_MASK ; 
 scalar_t__ TEST_BIT (size_t const,int) ; 
 int decode_add (size_t const*,TYPE_1__*) ; 
 char** instr_names ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,unsigned int) ; 

__attribute__((used)) static int decode_arith(const ut8 *bytes, ebc_command_t *cmd) {
	int ret = decode_add(bytes, cmd);
	unsigned bits = TEST_BIT (bytes[0], 6)? 64: 32;
	snprintf (cmd->instr, EBC_INSTR_MAXLEN, "%s%u",
			instr_names[bytes[0] & EBC_OPCODE_MASK], bits);
	return ret;
}