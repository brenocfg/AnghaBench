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
typedef  int /*<<< orphan*/  ut16 ;
struct TYPE_3__ {int size; int /*<<< orphan*/  family; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_FAMILY_FPU ; 

__attribute__((used)) static int fpu_insn(RAnal* anal, RAnalOp* op, ut16 code) {
	//Not interested on FPU stuff for now
	op->family = R_ANAL_OP_FAMILY_FPU;
	return op->size;
}