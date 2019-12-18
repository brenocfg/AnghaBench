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
	const char *p = \
		"=PC	pc\n"
		"=SP	y\n"
		"=A0	r24\n"
		"=A1	r25\n"
		"=A2	r26\n"
		"=A3	r27\n"
		"gpr	psr	.32	0	0\n"
		"gpr	pc	.32	4	0\n"
		"gpr	npc	.32	8	0\n"
		"gpr	y	.32	12	0\n"
		/* r0-r7 are global aka g0-g7 */
		"gpr	r0	.32	16	0\n"
		"gpr	r1	.32	20	0\n"
		"gpr	r2	.32	24	0\n"
		"gpr	r3	.32	28	0\n"
		"gpr	r4	.32	32	0\n"
		"gpr	r5	.32	36	0\n"
		"gpr	r6	.32	40	0\n"
		"gpr	r7	.32	44	0\n"
		/* r8-15 are out (o0-o7) */
		"gpr	r8	.32	48	0\n"
		"gpr	r9	.32	52	0\n"
		"gpr	r10	.32	56	0\n"
		"gpr	r11	.32	60	0\n"
		"gpr	r12	.32	64	0\n"
		"gpr	r13	.32	68	0\n"
		"gpr	r14	.32	72	0\n"
		"gpr	r15	.32	76	0\n"
		/* r16-23 are local (o0-o7) */
		"gpr	r16	.32	80	0\n"
		"gpr	r17	.32	84	0\n"
		"gpr	r18	.32	88	0\n"
		"gpr	r19	.32	92	0\n"
		"gpr	r20	.32	96	0\n"
		"gpr	r21	.32	100	0\n"
		"gpr	r22	.32	104	0\n"
		"gpr	r23	.32	108	0\n"
		/* r24-31 are in (i0-i7) */
		"gpr	r24	.32	112	0\n"
		"gpr	r25	.32	116	0\n"
		"gpr	r26	.32	120	0\n"
		"gpr	r27	.32	124	0\n"
		"gpr	r28	.32	128	0\n"
		"gpr	r29	.32	132	0\n"
		"gpr	r30	.32	136	0\n"
		"gpr	r31	.32	140	0\n"
	;
	return r_reg_set_profile_string (anal->reg, p);
}