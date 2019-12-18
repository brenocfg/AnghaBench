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
 int /*<<< orphan*/  r_anal_esil_pushnum (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * reil_pop_arg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reil_push_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reil_sub (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool reil_dec(RAnalEsil *esil) {
	RAnalReilArg *op = reil_pop_arg(esil);
	if (!op) {
		return false;
	}
	r_anal_esil_pushnum (esil, 1);
	reil_push_arg (esil, op);
	reil_sub (esil);
	R_FREE (op);
	return true;
}