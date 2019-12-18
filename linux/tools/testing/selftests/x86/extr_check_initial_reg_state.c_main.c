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
 int /*<<< orphan*/  SHOW (scalar_t__) ; 
 scalar_t__ ax ; 
 scalar_t__ bp ; 
 scalar_t__ bx ; 
 scalar_t__ cx ; 
 scalar_t__ di ; 
 scalar_t__ dx ; 
 int flags ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ r10 ; 
 scalar_t__ r11 ; 
 scalar_t__ r12 ; 
 scalar_t__ r13 ; 
 scalar_t__ r14 ; 
 scalar_t__ r15 ; 
 scalar_t__ r8 ; 
 scalar_t__ r9 ; 
 scalar_t__ si ; 
 scalar_t__ sp ; 

int main()
{
	int nerrs = 0;

	if (sp == 0) {
		printf("[FAIL]\tTest was built incorrectly\n");
		return 1;
	}

	if (ax || bx || cx || dx || si || di || bp
#ifdef __x86_64__
	    || r8 || r9 || r10 || r11 || r12 || r13 || r14 || r15
#endif
		) {
		printf("[FAIL]\tAll GPRs except SP should be 0\n");
#define SHOW(x) printf("\t" #x " = 0x%lx\n", x);
		SHOW(ax);
		SHOW(bx);
		SHOW(cx);
		SHOW(dx);
		SHOW(si);
		SHOW(di);
		SHOW(bp);
		SHOW(sp);
#ifdef __x86_64__
		SHOW(r8);
		SHOW(r9);
		SHOW(r10);
		SHOW(r11);
		SHOW(r12);
		SHOW(r13);
		SHOW(r14);
		SHOW(r15);
#endif
		nerrs++;
	} else {
		printf("[OK]\tAll GPRs except SP are 0\n");
	}

	if (flags != 0x202) {
		printf("[FAIL]\tFLAGS is 0x%lx, but it should be 0x202\n", flags);
		nerrs++;
	} else {
		printf("[OK]\tFLAGS is 0x202\n");
	}

	return nerrs ? 1 : 0;
}