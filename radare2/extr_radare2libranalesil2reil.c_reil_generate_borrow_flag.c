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
typedef  int ut8 ;
struct TYPE_13__ {TYPE_1__* Reil; } ;
struct TYPE_12__ {int /*<<< orphan*/  cur; int /*<<< orphan*/  old; } ;
typedef  int /*<<< orphan*/  RAnalReilArg ;
typedef  TYPE_2__ RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_anal_esil_push (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_anal_esil_pushnum (TYPE_2__*,int) ; 
 int /*<<< orphan*/  reil_add (TYPE_2__*) ; 
 int /*<<< orphan*/  reil_and (TYPE_2__*) ; 
 int /*<<< orphan*/  reil_generate_mask (TYPE_2__*) ; 
 int /*<<< orphan*/  reil_larger (TYPE_2__*) ; 
 int /*<<< orphan*/ * reil_pop_arg (TYPE_2__*) ; 
 int /*<<< orphan*/  reil_push_arg (TYPE_2__*,int /*<<< orphan*/ *) ; 

void reil_generate_borrow_flag(RAnalEsil *esil, ut8 bit) {
	RAnalReilArg *op1;

	r_anal_esil_pushnum(esil, bit);
	r_anal_esil_pushnum(esil, 0x3f);
	reil_and(esil);
	r_anal_esil_pushnum(esil, 0x3f);
	reil_add(esil);
	r_anal_esil_pushnum(esil, 0x3f);
	reil_and(esil);
	// Generate the mask. 2 << bits - 1
	reil_generate_mask(esil);
	op1 = reil_pop_arg(esil);
	// old & mask
	r_anal_esil_push(esil, esil->Reil->old);
	reil_push_arg(esil, op1);
	reil_and(esil);
	// cur & mask
	r_anal_esil_push(esil, esil->Reil->cur);
	reil_push_arg(esil, op1);
	reil_and(esil);
	// Check
	reil_larger(esil);

	free (op1);
}