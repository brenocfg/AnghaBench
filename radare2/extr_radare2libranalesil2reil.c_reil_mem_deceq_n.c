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
typedef  int /*<<< orphan*/  RAnalReilArg ;
typedef  int /*<<< orphan*/  RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  REIL_SUB ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_anal_esil_pushnum (int /*<<< orphan*/ *,int) ; 
 int reil_mem_bineq_n (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reil_pop_arg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reil_push_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reil_mem_deceq_n(RAnalEsil *esil, ut8 size) {
	int ret = 1;
	RAnalReilArg *op1 = reil_pop_arg(esil);
	if (!op1) {
		return false;
	}

	r_anal_esil_pushnum(esil, 1);
	reil_push_arg(esil, op1);
	ret &= reil_mem_bineq_n(esil, REIL_SUB, size);

	free (op1);
	return ret;
}