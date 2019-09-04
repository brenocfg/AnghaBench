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
 int R_ANAL_COND_EQ ; 
 int R_ANAL_COND_GE ; 
 int R_ANAL_COND_GT ; 
 int R_ANAL_COND_LE ; 
 int R_ANAL_COND_LT ; 
 int R_ANAL_COND_NE ; 
#define  X86_INS_JA 145 
#define  X86_INS_JAE 144 
#define  X86_INS_JB 143 
#define  X86_INS_JBE 142 
#define  X86_INS_JCXZ 141 
#define  X86_INS_JE 140 
#define  X86_INS_JECXZ 139 
#define  X86_INS_JG 138 
#define  X86_INS_JGE 137 
#define  X86_INS_JL 136 
#define  X86_INS_JLE 135 
#define  X86_INS_JNE 134 
#define  X86_INS_JNO 133 
#define  X86_INS_JNP 132 
#define  X86_INS_JNS 131 
#define  X86_INS_JO 130 
#define  X86_INS_JP 129 
#define  X86_INS_JS 128 

__attribute__((used)) static int cond_x862r2(int id) {
	switch (id) {
	case X86_INS_JE:
		return R_ANAL_COND_EQ;
	case X86_INS_JNE:
		return R_ANAL_COND_NE;
	case X86_INS_JB:
	case X86_INS_JL:
		return R_ANAL_COND_LT;
	case X86_INS_JBE:
	case X86_INS_JLE:
		return R_ANAL_COND_LE;
	case X86_INS_JG:
	case X86_INS_JA:
		return R_ANAL_COND_GT;
	case X86_INS_JAE:
		return R_ANAL_COND_GE;
	case X86_INS_JS:
	case X86_INS_JNS:
	case X86_INS_JO:
	case X86_INS_JNO:
	case X86_INS_JGE:
	case X86_INS_JP:
	case X86_INS_JNP:
	case X86_INS_JCXZ:
	case X86_INS_JECXZ:
		break;
	}
	return 0;
}