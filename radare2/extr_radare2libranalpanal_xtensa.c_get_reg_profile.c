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
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 char* strdup (char*) ; 

__attribute__((used)) static char *get_reg_profile(RAnal *anal) {
	return strdup (
		// Assuming call0 ABI
		"# a0		return address\n"
		"# a1		stack pointer\n"
		"# a2-a7	arguments\n"
		"# a2-a5	return value (call0 ABI)\n"
		"# a12-a15	callee-saved (call0 ABI)\n"
		"=PC	pc\n"
		"=BP	a14\n"
		"=SP	a1\n"
		"=A0	a2\n"
		"=A1	a3\n"
		"=A2	a4\n"
		"=A3	a5\n"
		"=A4	a6\n"
		"=A5	a7\n"
		"gpr	a0	.32	0	0\n"
		"gpr	a1	.32	4	0\n"
		"gpr	a2	.32	8	0\n"
		"gpr	a3	.32	16	0\n"
		"gpr	a4	.32	20	0\n"
		"gpr	a5	.32	24	0\n"
		"gpr	a6	.32	28	0\n"
		"gpr	a7	.32	32	0\n"
		"gpr	a8	.32	36	0\n"
		"gpr	a9	.32	40	0\n"
		"gpr	a10	.32	44	0\n"
		"gpr	a11	.32	48	0\n"
		"gpr	a12	.32	52	0\n"
		"gpr	a13	.32	56	0\n"
		"gpr	a14	.32	60	0\n"
		"gpr	a15	.32	64	0\n"

		// pc
		"gpr	pc	.32	68	0\n"

		// sr
		"gpr	sar	.32	72	0\n"
	);
}