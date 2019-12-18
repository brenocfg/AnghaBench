#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ut32 ;
struct TYPE_6__ {int operands_count; TYPE_1__* operands; } ;
struct TYPE_5__ {int reg; } ;
typedef  TYPE_2__ ArmOp ;

/* Variables and functions */
 int arithmetic (TYPE_2__*,int) ; 

__attribute__((used)) static ut32 neg(ArmOp *op) {
	if (op->operands_count < 2) {
		return -1;
	}
	op->operands_count++;
	op->operands[2] = op->operands[1];
	op->operands[1].reg = 31; // xzr

	return arithmetic (op, 0xd1); // sub reg0, xzr, reg1
}