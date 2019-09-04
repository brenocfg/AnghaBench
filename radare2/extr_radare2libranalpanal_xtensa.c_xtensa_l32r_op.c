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
typedef  int ut8 ;
typedef  int ut64 ;
struct TYPE_3__ {int ptr; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_TYPE_LOAD ; 

__attribute__((used)) static void xtensa_l32r_op (RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf) {
	op->type = R_ANAL_OP_TYPE_LOAD;
	op->ptr = ((addr + 3) & ~3) + ((buf[2] << 8 | buf[1]) << 2) - 0x40000;
}