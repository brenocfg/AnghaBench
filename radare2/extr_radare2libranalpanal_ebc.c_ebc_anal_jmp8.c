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
typedef  int /*<<< orphan*/  ut8 ;
typedef  void* ut64 ;
typedef  int int8_t ;
struct TYPE_3__ {int /*<<< orphan*/  type; void* fail; void* addr; void* jump; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_TYPE_CJMP ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_JMP ; 
 scalar_t__ TEST_BIT (int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static void ebc_anal_jmp8(RAnalOp *op, ut64 addr, const ut8 *buf) {
	int jmpadr = (int8_t)buf[1];
	op->jump = addr + 2 + (jmpadr * 2);
	op->addr = addr;
	op->fail = addr + 2;

	if (TEST_BIT(buf[0], 7)) {
		op->type = R_ANAL_OP_TYPE_CJMP;
	} else {
		op->type = R_ANAL_OP_TYPE_JMP;
	}
}