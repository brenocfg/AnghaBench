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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  RAnalReilOpcode ;
typedef  int /*<<< orphan*/  RAnalReilArg ;
typedef  int /*<<< orphan*/  RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int reil_binop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int reil_peekn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int reil_poken (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reil_pop_arg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reil_push_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool reil_mem_bineq_n(RAnalEsil *esil, RAnalReilOpcode opcode, ut8 size) {
	int ret = 1;
	RAnalReilArg *op2, *op1;

	op2 = reil_pop_arg (esil);
	if (!op2) {
		return false;
	}
	op1 = reil_pop_arg (esil);
	if (!op1) {
		R_FREE (op2);
		return false;
	}

	reil_push_arg(esil, op2);
	ret &= reil_peekn(esil, size);
	reil_push_arg(esil, op1);
	ret &= reil_binop(esil, opcode);
	reil_push_arg(esil, op2);
	ret &= reil_poken(esil, size);

	free (op2);
	free (op1);
	return ret;
}