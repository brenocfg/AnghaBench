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
struct TYPE_3__ {int value; } ;
typedef  TYPE_1__ RAsmLm32Instruction ;

/* Variables and functions */
 int RAsmLm32InstrImm5InvalidBitsMask ; 

__attribute__((used)) static bool is_invalid_imm5_instr(RAsmLm32Instruction *instr) {
	return instr->value & RAsmLm32InstrImm5InvalidBitsMask;
}