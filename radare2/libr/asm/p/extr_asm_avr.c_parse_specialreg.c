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
struct TYPE_2__ {int operandType; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int OPERAND_YPQ ; 
 int OPERAND_ZPQ ; 
 int REGS_TABLE ; 
 TYPE_1__* RegsTable ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int parse_specialreg(const char *reg) {
	const int len = strlen (reg);
	int i, found = -1;

	if (len > 0) {
		for (i = 0; i < REGS_TABLE; i++) {
			if (!strncmp (RegsTable[i].reg, reg, 4)) {
				found = RegsTable[i].operandType;
				break;
			}
		}
		/* radare tolower instruction in rasm, so we use 'y' instead of 'Y'
		and so on for other registers */
		if (found == -1 && reg[1] == '+') {
			if (reg[0] == 'y' && len > 2) {
				found = OPERAND_YPQ;
			} else if (reg[0] == 'z' && len > 2) {
				found = OPERAND_ZPQ;
			}
		}
		if (found == -1 && reg[2] == '+') {
			if (reg[0] == 'y' && len > 2) {
				found = OPERAND_YPQ;
			} else if (reg[0] == 'z' && len > 2) {
				found = OPERAND_ZPQ;
			}
		}
	}
	return found;
}