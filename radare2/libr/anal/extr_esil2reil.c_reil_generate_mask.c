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
typedef  int /*<<< orphan*/  RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  r_anal_esil_pushnum (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reil_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reil_lsl (int /*<<< orphan*/ *) ; 

void reil_generate_mask(RAnalEsil *esil) {
	r_anal_esil_pushnum(esil, 2);
	reil_lsl(esil);
	reil_dec(esil);
}