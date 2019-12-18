#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* Reil; } ;
struct TYPE_12__ {int /*<<< orphan*/  cur; } ;
typedef  int /*<<< orphan*/  RAnalReilArg ;
typedef  TYPE_2__ RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_anal_esil_push (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_anal_esil_pushnum (TYPE_2__*,int) ; 
 int /*<<< orphan*/  reil_and (TYPE_2__*) ; 
 int /*<<< orphan*/  reil_lsr (TYPE_2__*) ; 
 int /*<<< orphan*/  reil_not (TYPE_2__*) ; 
 int /*<<< orphan*/ * reil_pop_arg (TYPE_2__*) ; 
 int /*<<< orphan*/  reil_push_arg (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reil_xor (TYPE_2__*) ; 

void reil_generate_partity_flag(RAnalEsil *esil) {
	// Generation of parity flag taken from openreil README example.
	RAnalReilArg *op;
	r_anal_esil_push(esil, esil->Reil->cur);
	r_anal_esil_pushnum(esil, 0xff);
	reil_and(esil);
	op = reil_pop_arg(esil);
	if (!op) {
		return;
	}

	r_anal_esil_pushnum(esil, 7);
	reil_push_arg(esil, op);
	reil_lsr(esil);
	r_anal_esil_pushnum(esil, 6);
	reil_push_arg(esil, op);
	reil_lsr(esil);
	reil_xor(esil);
	r_anal_esil_pushnum(esil, 5);
	reil_push_arg(esil, op);
	reil_lsr(esil);
	r_anal_esil_pushnum(esil, 4);
	reil_push_arg(esil, op);
	reil_lsr(esil);
	reil_xor(esil);
	reil_xor(esil);
	r_anal_esil_pushnum(esil, 3);
	reil_push_arg(esil, op);
	reil_lsr(esil);
	r_anal_esil_pushnum(esil, 2);
	reil_push_arg(esil, op);
	reil_lsr(esil);
	reil_xor(esil);
	r_anal_esil_pushnum(esil, 1);
	reil_push_arg(esil, op);
	reil_lsr(esil);
	reil_push_arg(esil, op);
	reil_xor(esil);
	reil_xor(esil);
	reil_xor(esil);
	r_anal_esil_pushnum(esil, 1);
	reil_and(esil);
	reil_not(esil);

	free (op);
}