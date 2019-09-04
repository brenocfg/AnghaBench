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
struct cr16_cmd {int /*<<< orphan*/  operands; } ;

/* Variables and functions */
 scalar_t__ CR16_INSTR_MAXLEN ; 
 scalar_t__ cr16_check_reg_boundaries (size_t) ; 
 char** cr16_regs_names ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,char*,char*) ; 

__attribute__((used)) static inline int cr16_print_reg_reg(struct cr16_cmd *cmd, ut8 src, ut8 dst)
{
	if (cr16_check_reg_boundaries(src) || cr16_check_reg_boundaries(dst)) {
		return -1;
	}

	snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1, "%s,%s",
			cr16_regs_names[src], cr16_regs_names[dst]);

	return 0;
}