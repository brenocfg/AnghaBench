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
typedef  int /*<<< orphan*/  RAnalReilArg ;
typedef  int /*<<< orphan*/  RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * reil_pop_arg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reil_push_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reil_smaller_equal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool reil_larger_equal(RAnalEsil *esil) {
	RAnalReilArg *op2, *op1;

	op2 = reil_pop_arg(esil);
	if (!op2) {
		return false;
	}
	op1 = reil_pop_arg(esil);
	if (!op1) {
		R_FREE (op2);
		return false;
	}

	reil_push_arg (esil, op2);
	reil_push_arg (esil, op1);
	reil_smaller_equal (esil);
	R_FREE (op1);
	R_FREE (op2);
	return true;
}