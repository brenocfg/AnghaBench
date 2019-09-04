#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_6__ {int /*<<< orphan*/  family; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_FAMILY_FPU ; 
 int /*<<< orphan*/  xtensa_load_op (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/  xtensa_store_op (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/  xtensa_unk_op (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int const*) ; 

__attribute__((used)) static void xtensa_lsci_op (RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf) {
	ut8 r = buf[1] >> 4;
	op->family = R_ANAL_OP_FAMILY_FPU;
	if ((r & 3) == 0) {
		if (r & 4) {
			xtensa_store_op (anal, op, addr, buf);
		} else {
			xtensa_load_op (anal, op, addr, buf);
		}
	} else {
		xtensa_unk_op (anal, op, addr, buf);
	}
}