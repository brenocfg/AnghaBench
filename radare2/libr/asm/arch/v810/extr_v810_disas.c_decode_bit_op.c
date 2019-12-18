#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t ut8 ;
typedef  int /*<<< orphan*/  ut16 ;
struct v810_cmd {int /*<<< orphan*/  instr; } ;

/* Variables and functions */
 size_t REG1 (int /*<<< orphan*/  const) ; 
 scalar_t__ V810_INSTR_MAXLEN ; 
 char** bit_instrs ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,char*) ; 

__attribute__((used)) static int decode_bit_op(const ut16 instr, struct v810_cmd *cmd) {
	ut8 subop;

	subop = REG1(instr);
	snprintf (cmd->instr, V810_INSTR_MAXLEN - 1, "%s", bit_instrs[subop]);

	return 2;
}