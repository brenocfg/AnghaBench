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
struct TYPE_3__ {int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ RAnal ;

/* Variables and functions */
 int r_reg_set_profile_string (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int sh_set_reg_profile(RAnal* anal) {
	//TODO Add system ( ssr, spc ) + fpu regs
	const char *p =
		"=PC	pc\n"
		"=SN	r0\n"
		"=SP	r15\n"
		"=BP	r14\n"
		"=A0	r4\n"
		"=A1	r5\n"
		"=A2	r6\n"
		"=A3	r7\n"
		"=R0	r0\n"
		"gpr	r0	.32	0	0\n"
		"gpr	r1	.32	4	0\n"
		"gpr	r2	.32	8	0\n"
		"gpr	r3	.32	12	0\n"
		"gpr	r4	.32	16	0\n"
		"gpr	r5	.32	20	0\n"
		"gpr	r6	.32	24	0\n"
		"gpr	r7	.32	28	0\n"
		"gpr	r8	.32	32	0\n"
		"gpr	r9	.32	36	0\n"
		"gpr	r10	.32	40	0\n"
		"gpr	r11	.32	44	0\n"
		"gpr	r12	.32	48	0\n"
		"gpr	r13	.32	52	0\n"
		"gpr	r14	.32	56	0\n"
		"gpr	r15	.32	60	0\n"
		"gpr	pc	.32	64	0\n"
		"gpr	pr	.32	68	0\n"
		"gpr	sr	.32	72	0\n"
		"gpr	gbr	.32	76	0\n"
		"gpr	vbr	.32	80	0\n"
		"gpr	mach	.32	84	0\n"
		"gpr	macl	.32	88	0\n";
	return r_reg_set_profile_string(anal->reg, p);
}