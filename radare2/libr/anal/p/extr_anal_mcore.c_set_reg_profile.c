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

__attribute__((used)) static int set_reg_profile(RAnal *anal) {
	const char *p;
	p = "=PC	pc\n"
		"=SP	r1\n"
		"=SR	sr\n"
		"=A0	r3\n"
		"=A1	r4\n"
		"=A2	r5\n"
		"=A3	r6\n"
		"=A4	r7\n"
		"=A5	r8\n"
		"=A6	r6\n"
		"gpr	r0	.32 0   0\n"
		"gpr	r1	.32 4   0\n"
		"gpr	r2	.32 8   0\n"
		"gpr	r3	.32 12  0\n"
		"gpr	r4	.32 16  0\n"
		"gpr	r5	.32 20  0\n"
		"gpr	r6	.32 24  0\n"
		"gpr	r7	.32 28  0\n"
		"gpr	r8	.32 32  0\n"
		"gpr	r9	.32 36  0\n"
		"gpr	r10   .32 40  0\n"
		"gpr	r11   .32 44  0\n"
		"gpr	r12   .32 48  0\n"
		"gpr	r13   .32 52  0\n"
		"gpr	r14   .32 56  0\n"
		"gpr	r15   .32 60  0\n"

		"gpr	psr   .32 64  0\n"
		"gpr	vbr   .32 68  0\n"
		"gpr	epsr  .32 72  0\n"
		"gpr	fpsr  .32 76  0\n"
		"gpr	epc   .32 80  0\n"
		"gpr	fpc   .32 84  0\n"
		"gpr	ss0   .32 88  0\n"
		"gpr	ss1   .32 92  0\n"
		"gpr	ss2   .32 96  0\n"
		"gpr	ss3   .32 100 0\n"
		"gpr	ss4   .32 104 0\n"
		"gpr	gcr   .32 108 0\n"
		"gpr	gsr   .32 112 0\n"
		"gpr	cpidr .32 116 0\n"
		"gpr	dcsr  .32 120 0\n"
		"gpr	cwr   .32 124 0\n"
		"gpr	cr16  .32 128 0\n"
		"gpr	cfr   .32 132 0\n"
		"gpr	ccr   .32 136 0\n"
		"gpr	capr  .32 140 0\n"
		"gpr	pacr  .32 144 0\n"
		"gpr	prsr  .32 148 0\n"

		"gpr	cr22  .32 152 0\n"
		"gpr	cr23  .32 156 0\n"
		"gpr	cr24  .32 160 0\n"
		"gpr	cr25  .32 164 0\n"
		"gpr	cr26  .32 168 0\n"
		"gpr	cr27  .32 172 0\n"
		"gpr	cr28  .32 176 0\n"
		"gpr	cr29  .32 180 0\n"
		"gpr	cr30  .32 184 0\n"
		"gpr	cr31  .32 188 0\n"
		"gpr	pc	.32 192 0\n";
	return r_reg_set_profile_string (anal->reg, p);
}