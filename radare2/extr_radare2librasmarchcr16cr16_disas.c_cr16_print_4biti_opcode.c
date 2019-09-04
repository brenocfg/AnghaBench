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
typedef  int /*<<< orphan*/  ut16 ;
struct cr16_cmd {int /*<<< orphan*/  instr; } ;

/* Variables and functions */
 scalar_t__ CR16_INSTR_MAXLEN ; 
 scalar_t__ cr16_check_instrs_4bit_bndrs (size_t) ; 
 scalar_t__ cr16_get_opcode_i (int /*<<< orphan*/ ) ; 
 size_t cr16_get_opcode_low (int /*<<< orphan*/ ) ; 
 char** instrs_4bit ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,char*,char) ; 

__attribute__((used)) static inline int cr16_print_4biti_opcode(struct cr16_cmd *cmd, ut16 instr)
{
	if (cr16_check_instrs_4bit_bndrs(cr16_get_opcode_low(instr))) {
		return -1;
	}

	snprintf(cmd->instr, CR16_INSTR_MAXLEN - 1, "%s%c",
			instrs_4bit[cr16_get_opcode_low(instr)],
			cr16_get_opcode_i(instr) ? 'w' : 'b');
	return 0;
}