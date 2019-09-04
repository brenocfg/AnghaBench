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
struct equation_coefs {int a1; int b1; int a2; int b2; } ;

/* Variables and functions */
 void* FIXPT_DIV (int,int) ; 
 int FIXPT_INT (int) ; 
 int TJ_1 ; 
 int TJ_3 ; 

__attribute__((used)) static void rcar_gen3_thermal_calc_coefs(struct equation_coefs *coef,
					 int *ptat, int *thcode)
{
	int tj_2;

	/* TODO: Find documentation and document constant calculation formula */

	/*
	 * Division is not scaled in BSP and if scaled it might overflow
	 * the dividend (4095 * 4095 << 14 > INT_MAX) so keep it unscaled
	 */
	tj_2 = (FIXPT_INT((ptat[1] - ptat[2]) * 157)
		/ (ptat[0] - ptat[2])) - FIXPT_INT(41);

	coef->a1 = FIXPT_DIV(FIXPT_INT(thcode[1] - thcode[2]),
			     tj_2 - FIXPT_INT(TJ_3));
	coef->b1 = FIXPT_INT(thcode[2]) - coef->a1 * TJ_3;

	coef->a2 = FIXPT_DIV(FIXPT_INT(thcode[1] - thcode[0]),
			     tj_2 - FIXPT_INT(TJ_1));
	coef->b2 = FIXPT_INT(thcode[0]) - coef->a2 * TJ_1;
}