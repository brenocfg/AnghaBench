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
typedef  int ut8 ;
typedef  int ut32 ;
struct cr16_cmd {int /*<<< orphan*/  operands; } ;

/* Variables and functions */
 scalar_t__ CR16_INSTR_MAXLEN ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,int,int) ; 

__attribute__((used)) static inline int cr16_print_short_abs18(struct cr16_cmd *cmd,
		ut8 sh, ut32 abs) {
	snprintf(cmd->operands, CR16_INSTR_MAXLEN - 1,
			"$0x%02x,0x%08x", sh, abs);
	return 0;
}