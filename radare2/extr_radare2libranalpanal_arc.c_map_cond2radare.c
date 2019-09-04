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
typedef  int ut8 ;

/* Variables and functions */
 int R_ANAL_COND_AL ; 
 int R_ANAL_COND_EQ ; 
 int R_ANAL_COND_GE ; 
 int R_ANAL_COND_GT ; 
 int R_ANAL_COND_HI ; 
 int R_ANAL_COND_LE ; 
 int R_ANAL_COND_LS ; 
 int R_ANAL_COND_LT ; 
 int R_ANAL_COND_MI ; 
 int R_ANAL_COND_NE ; 
 int R_ANAL_COND_PL ; 
 int R_ANAL_COND_VC ; 
 int R_ANAL_COND_VS ; 

__attribute__((used)) static int map_cond2radare(ut8 cond) {
	switch (cond) {
	case 0: return R_ANAL_COND_AL;
	case 1: return R_ANAL_COND_EQ;
	case 2: return R_ANAL_COND_NE;
	case 3: return R_ANAL_COND_PL;
	case 4: return R_ANAL_COND_MI;
	case 7: return R_ANAL_COND_VS;
	case 8: return R_ANAL_COND_VC;
	case 9: return R_ANAL_COND_GT;
	case 0xa: return R_ANAL_COND_GE;
	case 0xb: return R_ANAL_COND_LT;
	case 0xc: return R_ANAL_COND_LE;
	case 0xd: return R_ANAL_COND_HI;
	case 0xe: return R_ANAL_COND_LS;
#if 0
	/* TODO: */
	/* - radare defines R_ANAL_COND_LO as carry clear and _HS as carry set */
	/*   which appears different to the ARC definitions. */
	/*   Need to do some math and double check the details */
	case 5: return R_ANAL_COND_?? - CS,C,LO - Carry set & LO
	case 6: return R_ANAL_COND_?? - CC,NC,HS - Carry clear & HS
	/* - Positive non-zero doesnt map to any Radare cond code.  Perhaps just add it? */
	case 0xf: return R_ANAL_COND_?? - PNZ - Positive non-zero
#endif
	}
	return -1;
}