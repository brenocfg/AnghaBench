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
struct TYPE_3__ {int offset_sign; int /*<<< orphan*/ * scale; int /*<<< orphan*/  offset; int /*<<< orphan*/  type; int /*<<< orphan*/  reg; int /*<<< orphan*/ * regs; } ;
typedef  int /*<<< orphan*/  RAsm ;
typedef  TYPE_1__ Operand ;

/* Variables and functions */
 int /*<<< orphan*/  OT_MEMORY ; 
 int /*<<< orphan*/  getnum (int /*<<< orphan*/ *,char const*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static void parse_segment_offset(RAsm *a, const char *str, size_t *pos,
		Operand *op, int reg_index) {
	int nextpos = *pos;
	char *c = strchr (str + nextpos, ':');
	if (c) {
		nextpos ++; // Skip the ':'
		c = strchr (str + nextpos, '[');
		if (c) {nextpos ++;} // Skip the '['

		// Assign registers to match behaviour of OT_MEMORY type
		op->regs[reg_index] = op->reg;
		op->type |= OT_MEMORY;
		op->offset_sign = 1;
		char *p = strchr (str + nextpos, '-');
		if (p) {
			op->offset_sign = -1;
			nextpos ++;
		}
		op->scale[reg_index] = getnum (a, str + nextpos);
		op->offset = op->scale[reg_index];
	}
}