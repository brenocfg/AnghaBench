#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* Reil; } ;
struct TYPE_8__ {int lastsz; } ;
typedef  TYPE_2__ RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  r_anal_esil_pushnum (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reil_generate_borrow_flag (TYPE_2__*,int) ; 
 int /*<<< orphan*/  reil_generate_carry_flag (TYPE_2__*,int) ; 
 int /*<<< orphan*/  reil_xor (TYPE_2__*) ; 

void reil_generate_overflow_flag(RAnalEsil *esil) {
	if (esil->Reil->lastsz < 2) {
		r_anal_esil_pushnum (esil, 0);
	}

	reil_generate_borrow_flag(esil, esil->Reil->lastsz);
	reil_generate_carry_flag(esil, esil->Reil->lastsz - 2);
	reil_xor(esil);
}