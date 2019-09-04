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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  xtensa_load_op (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/  xtensa_store_op (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/  xtensa_unk_op (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const*) ; 

__attribute__((used)) static void xtensa_lsc4_op (RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf) {
	switch ((buf[2] >> 4) & 0xf) {
	case 0x0:
		xtensa_load_op (anal, op, addr, buf);
		break;
	case 0x4:
		xtensa_store_op (anal, op, addr, buf);
		break;
	default:
		xtensa_unk_op (anal, op, addr, buf);
		break;
	}
}