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
struct TYPE_3__ {int* operands; int /*<<< orphan*/  mnemonic; } ;
typedef  TYPE_1__ amd29k_instr_t ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

bool amd29k_instr_is_ret(amd29k_instr_t* instruction) {
	if (instruction && !strcmp (instruction->mnemonic, "calli") && instruction->operands[0] == 128 && instruction->operands[1] == 128) {
		return true;
	}
	return false;
}