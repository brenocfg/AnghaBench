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
#define  R_ANAL_COND_GE 131 
#define  R_ANAL_COND_GT 130 
#define  R_ANAL_COND_LE 129 
#define  R_ANAL_COND_LT 128 

__attribute__((used)) static int cond_invert (int cond) {
	int res = 0;
	switch (cond) {
	case R_ANAL_COND_LE:
		res = R_ANAL_COND_GT;
		break;
	case R_ANAL_COND_LT:
		res = R_ANAL_COND_GE;
		break;
	case R_ANAL_COND_GE:
		res = R_ANAL_COND_LT;
		break;
	case R_ANAL_COND_GT:
		res = R_ANAL_COND_LE;
		break;
	}
	return res;
}