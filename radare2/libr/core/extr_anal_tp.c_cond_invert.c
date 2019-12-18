#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int _RAnalCond ;
struct TYPE_3__ {int /*<<< orphan*/  verbose; } ;
typedef  TYPE_1__ RAnal ;

/* Variables and functions */
#define  R_ANAL_COND_GE 131 
#define  R_ANAL_COND_GT 130 
#define  R_ANAL_COND_LE 129 
#define  R_ANAL_COND_LT 128 
 int /*<<< orphan*/  eprintf (char*) ; 

__attribute__((used)) static _RAnalCond cond_invert(RAnal *anal, _RAnalCond cond) {
	switch (cond) {
	case R_ANAL_COND_LE:
		return R_ANAL_COND_GT;
	case R_ANAL_COND_LT:
		return R_ANAL_COND_GE;
	case R_ANAL_COND_GE:
		return R_ANAL_COND_LT;
	case R_ANAL_COND_GT:
		return R_ANAL_COND_LE;
	default:
		if (anal->verbose) {
			eprintf ("Unhandled conditional swap\n");
		}
		break;
	}
	return 0; // 0 is COND_ALways...
	/* I haven't looked into it but I suspect that this might be confusing:
	the opposite of any condition not in the list above is "always"? */
}