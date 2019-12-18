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
typedef  int ut16 ;
struct v810_cmd {int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;
typedef  int st16 ;

/* Variables and functions */
 int DISP9 (int const) ; 
 size_t V810_COND_NOP ; 
 scalar_t__ V810_INSTR_MAXLEN ; 
 char** conds ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 

__attribute__((used)) static int decode_bcond(const ut16 instr, struct v810_cmd *cmd) {
	st16 disp;
	ut8 cond;

	cond = (instr >> 9) & 0xF;
	disp = DISP9(instr);

	if (cond == V810_COND_NOP) {
		snprintf (cmd->instr, V810_INSTR_MAXLEN - 1, "nop");
	} else {
		snprintf (cmd->instr, V810_INSTR_MAXLEN - 1, "b%s", conds[cond]);
		snprintf (cmd->operands, V810_INSTR_MAXLEN - 1, "%d", disp);
	}

	return 2;
}