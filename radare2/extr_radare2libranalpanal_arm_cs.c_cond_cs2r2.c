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

/* Variables and functions */
 int ARM_CC_AL ; 
#define  ARM_CC_EQ 141 
#define  ARM_CC_GE 140 
#define  ARM_CC_GT 139 
#define  ARM_CC_HI 138 
#define  ARM_CC_HS 137 
#define  ARM_CC_LE 136 
#define  ARM_CC_LO 135 
#define  ARM_CC_LS 134 
#define  ARM_CC_LT 133 
#define  ARM_CC_MI 132 
#define  ARM_CC_NE 131 
#define  ARM_CC_PL 130 
#define  ARM_CC_VC 129 
#define  ARM_CC_VS 128 
 int R_ANAL_COND_AL ; 
 int R_ANAL_COND_EQ ; 
 int R_ANAL_COND_GE ; 
 int R_ANAL_COND_GT ; 
 int R_ANAL_COND_HI ; 
 int R_ANAL_COND_HS ; 
 int R_ANAL_COND_LE ; 
 int R_ANAL_COND_LO ; 
 int R_ANAL_COND_LS ; 
 int R_ANAL_COND_LT ; 
 int R_ANAL_COND_MI ; 
 int R_ANAL_COND_NE ; 
 int R_ANAL_COND_PL ; 
 int R_ANAL_COND_VC ; 
 int R_ANAL_COND_VS ; 

__attribute__((used)) static int cond_cs2r2(int cc) {
	if (cc == ARM_CC_AL || cc < 0) {
		cc = R_ANAL_COND_AL;
	} else {
		switch (cc) {
		case ARM_CC_EQ: cc = R_ANAL_COND_EQ; break;
		case ARM_CC_NE: cc = R_ANAL_COND_NE; break;
		case ARM_CC_HS: cc = R_ANAL_COND_HS; break;
		case ARM_CC_LO: cc = R_ANAL_COND_LO; break;
		case ARM_CC_MI: cc = R_ANAL_COND_MI; break;
		case ARM_CC_PL: cc = R_ANAL_COND_PL; break;
		case ARM_CC_VS: cc = R_ANAL_COND_VS; break;
		case ARM_CC_VC: cc = R_ANAL_COND_VC; break;

		case ARM_CC_HI: cc = R_ANAL_COND_HI; break;
		case ARM_CC_LS: cc = R_ANAL_COND_LS; break;
		case ARM_CC_GE: cc = R_ANAL_COND_GE; break;
		case ARM_CC_LT: cc = R_ANAL_COND_LT; break;
		case ARM_CC_GT: cc = R_ANAL_COND_GT; break;
		case ARM_CC_LE: cc = R_ANAL_COND_LE; break;
		}
	}
	return cc;
}