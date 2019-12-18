#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_8__ {scalar_t__ cpu; } ;
typedef  int (* TMS_ANAL_OP_FN ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ;
typedef  int /*<<< orphan*/  RAnalOpMask ;
typedef  int /*<<< orphan*/  RAnalOp ;
typedef  TYPE_1__ RAnal ;

/* Variables and functions */
 scalar_t__ r_str_casecmp (scalar_t__,char*) ; 
 int tms320_c54x_op (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int tms320_c55x_op (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int tms320_c55x_plus_op (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int tms320c64x_analop (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

int tms320_op(RAnal * anal, RAnalOp * op, ut64 addr, const ut8 * buf, int len, RAnalOpMask mask) {
	TMS_ANAL_OP_FN aop = tms320_c55x_op;

	if (anal->cpu && r_str_casecmp(anal->cpu, "c64x") == 0) {
#ifdef CAPSTONE_TMS320C64X_H
		return tms320c64x_analop (anal, op, addr, buf, len, mask);
#else
		return -1;
#endif
	}
	if (anal->cpu && r_str_casecmp(anal->cpu, "c54x") == 0) {
		aop = tms320_c54x_op;
	} else if (anal->cpu && r_str_casecmp(anal->cpu, "c55x") == 0) {
		aop = tms320_c55x_op;
	} else if (anal->cpu && r_str_casecmp(anal->cpu, "c55x+") == 0) {
		aop = tms320_c55x_plus_op;
	}
	return aop (anal, op, addr, buf, len);
}