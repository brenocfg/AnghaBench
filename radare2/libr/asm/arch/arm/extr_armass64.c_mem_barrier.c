#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
typedef  int ut32 ;
struct TYPE_5__ {int operands_count; TYPE_1__* operands; int /*<<< orphan*/  mnemonic; } ;
struct TYPE_4__ {int mem_option; scalar_t__ type; int immediate; } ;
typedef  TYPE_2__ ArmOp ;

/* Variables and functions */
 scalar_t__ ARM_CONSTANT ; 
 scalar_t__ ARM_MEM_OPT ; 
 scalar_t__ ARM_NOTYPE ; 
 int UT32_MAX ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ut32 mem_barrier (ArmOp *op, ut64 addr, int k) {
	ut32 data = UT32_MAX;
	data = k;
	if (!strncmp (op->mnemonic, "isb", 3)) {
		if (op->operands[0].mem_option == 15 || op->operands[0].type == ARM_NOTYPE) {
			return data;
		} else {
			return UT32_MAX;
		}
	}
	if (op->operands[0].type == ARM_MEM_OPT) {
		data |= op->operands[0].mem_option << 16;
	} else if (op->operands_count == 1 && op->operands[0].type == ARM_CONSTANT) {
		data |= (op->operands[0].immediate << 16);
	}
	return data;
}