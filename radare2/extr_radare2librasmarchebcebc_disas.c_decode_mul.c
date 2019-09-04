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
struct TYPE_4__ {int /*<<< orphan*/  instr; } ;
typedef  TYPE_1__ ebc_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBC_INSTR_MAXLEN ; 
 size_t EBC_MUL ; 
 scalar_t__ TEST_BIT (int /*<<< orphan*/  const,int) ; 
 int decode_add (int /*<<< orphan*/  const*,TYPE_1__*) ; 
 char** instr_names ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,unsigned int) ; 

__attribute__((used)) static int decode_mul(const ut8 *bytes, ebc_command_t *cmd) {
	int ret = decode_add(bytes, cmd);
	unsigned bits = TEST_BIT (bytes[0], 6)? 64: 32;
	snprintf (cmd->instr, EBC_INSTR_MAXLEN, "%s%u",
			instr_names[EBC_MUL], bits);
	return ret;
}