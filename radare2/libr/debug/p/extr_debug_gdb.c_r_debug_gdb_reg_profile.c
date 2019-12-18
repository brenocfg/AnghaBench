#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* regprofile; scalar_t__ valid; } ;
struct TYPE_10__ {TYPE_2__ target; } ;
struct TYPE_9__ {TYPE_1__* anal; int /*<<< orphan*/  arch; } ;
struct TYPE_7__ {int bits; } ;
typedef  TYPE_3__ RDebug ;

/* Variables and functions */
#define  R_SYS_ARCH_ARM 134 
#define  R_SYS_ARCH_AVR 133 
#define  R_SYS_ARCH_LM32 132 
#define  R_SYS_ARCH_MIPS 131 
#define  R_SYS_ARCH_SH 130 
#define  R_SYS_ARCH_V850 129 
#define  R_SYS_ARCH_X86 128 
 int /*<<< orphan*/  check_connection (TYPE_3__*) ; 
 TYPE_5__* desc ; 
 int r_sys_arch_id (int /*<<< orphan*/ ) ; 
 char const* strdup (char*) ; 

__attribute__((used)) static const char *r_debug_gdb_reg_profile(RDebug *dbg) {
	int arch = r_sys_arch_id (dbg->arch);
	int bits = dbg->anal->bits;
	check_connection (dbg);
	if (desc && desc->target.valid && desc->target.regprofile) {
		return strdup (desc->target.regprofile);
	}
	switch (arch) {
	case R_SYS_ARCH_X86:
		if (bits == 16 || bits == 32) {
			return strdup (
				"=PC	eip\n"
				"=SP	esp\n"
				"=BP	ebp\n"
				"=A0	eax\n"
				"=A1	ebx\n"
				"=A2	ecx\n"
				"=A3	edx\n"
				"=SN	oeax\n"
				"gpr	eax	.32	0	0\n"
				"gpr	ecx	.32	4	0\n"
				"gpr	edx	.32	8	0\n"
				"gpr	ebx	.32	12	0\n"
				"gpr	esp	.32	16	0\n"
				"gpr	ebp	.32	20	0\n"
				"gpr	esi	.32	24	0\n"
				"gpr	edi	.32	28	0\n"
				"gpr	eip	.32	32	0\n"
				"gpr	eflags	.32	36	0\n"
				"seg	cs	.32	40	0\n"
				"seg	ss	.32	44	0\n"
				"seg	ds	.32	48	0\n"
				"seg	es	.32	52	0\n"
				"seg	fs	.32	56	0\n"
				"seg	gs	.32	60	0\n"
				"fpu	st0	.80	64	0\n"
				"fpu	st1	.80	74	0\n"
				"fpu	st2	.80	84	0\n"
				"fpu	st3	.80	94	0\n"
				"fpu	st4	.80	104	0\n"
				"fpu	st5	.80	114	0\n"
				"fpu	st6	.80	124	0\n"
				"fpu	st7	.80	134	0\n"
				"gpr	fctrl	.32	144	0\n"
				"gpr	fstat	.32	148	0\n"
				"gpr	ftag	.32	152	0\n"
				"gpr	fiseg	.32	156	0\n"
				"gpr	fioff	.32	160	0\n"
				"gpr	foseg	.32	164	0\n"
				"gpr	fooff	.32	168	0\n"
				"gpr	fop	.32	172	0\n"
			/* Commented until the long registers will be implemented
				"gpr	xmm0	.128	176	0\n"
				"gpr	xmm1	.128	192	0\n"
				"gpr	xmm2	.128	208	0\n"
				"gpr	xmm3	.128	224	0\n"
				"gpr	xmm4	.128	240	0\n"
				"gpr	xmm5	.128	256	0\n"
				"gpr	xmm6	.128	272	0\n"
				"gpr	xmm7	.128	288	0\n"
				"gpr	mxcsr	.32	304	0\n"
			*/
				);
		} else if (dbg->anal->bits == 64) {
			return strdup (
				"=PC	rip\n"
				"=SP	rsp\n"
				"=BP	rbp\n"
				"=A0	rax\n"
				"=A1	rbx\n"
				"=A2	rcx\n"
				"=A3	rdx\n"
				"=SN	orax\n"
				"gpr	fake	.64	795	0\n"
				"gpr	rax	.64	0	0\n"
				"gpr	rbx	.64	8	0\n"
				"gpr	rcx	.64	16	0\n"
				"gpr	rdx	.64	24	0\n"
				"gpr	rsi	.64	32	0\n"
				"gpr	rdi	.64	40	0\n"
				"gpr	rbp	.64	48	0\n"
				"gpr	rsp	.64	56	0\n"
				"gpr	r8	.64	64	0\n"
				"gpr	r9	.64	72	0\n"
				"gpr	r10	.64	80	0\n"
				"gpr	r11	.64	88	0\n"
				"gpr	r12	.64	96	0\n"
				"gpr	r13	.64	104	0\n"
				"gpr	r14	.64	112	0\n"
				"gpr	r15	.64	120	0\n"
				"gpr	rip	.64	128	0\n"
				"gpr	eflags	.32	136	0\n"
				"seg	cs	.32	140	0\n"
				"seg	ss	.32	144	0\n"
				"seg	ds	.32	148	0\n"
				"seg	es	.32	152	0\n"
				"seg	fs	.32	156	0\n"
				"seg	gs	.32	160	0\n"
				"fpu	st0	.80	164	0\n"
				"fpu	st1	.80	174	0\n"
				"fpu	st2	.80	184	0\n"
				"fpu	st3	.80	194	0\n"
				"fpu	st4	.80	204	0\n"
				"fpu	st5	.80	214	0\n"
				"fpu	st6	.80	224	0\n"
				"fpu	st7	.80	234	0\n"
				"gpr	fctrl	.32	244	0\n"
				"gpr	fstat	.32	248	0\n"
				"gpr	ftag	.32	252	0\n"
				"gpr	fiseg	.32	256	0\n"
				"gpr	fioff	.32	260	0\n"
				"gpr	foseg	.32	264	0\n"
				"gpr	fooff	.32	268	0\n"
				"gpr	fop	.32	272	0\n"
			/* Commented until the long registers will be implemented
				"gpr	xmm0	.128	276	0\n"
				"gpr	xmm1	.128	292	0\n"
				"gpr	xmm2	.128	308	0\n"
				"gpr	xmm3	.128	324	0\n"
				"gpr	xmm4	.128	340	0\n"
				"gpr	xmm5	.128	356	0\n"
				"gpr	xmm6	.128	372	0\n"
				"gpr	xmm7	.128	388	0\n"
				"gpr	xmm8	.128	404	0\n"
				"gpr	xmm9	.128	420	0\n"
				"gpr	xmm10	.128	436	0\n"
				"gpr	xmm11	.128	452	0\n"
				"gpr	xmm12	.128	468	0\n"
				"gpr	xmm13	.128	484	0\n"
				"gpr	xmm14	.128	500	0\n"
				"gpr	xmm15	.128	516	0\n"
				"gpr	mxcsr	.32	532	0\n"
			*/
			);
		} else {
			return strdup (
			"=PC	eip\n"
			"=SP	esp\n"
			"=BP	ebp\n"
			"=A0	eax\n"
			"=A1	ebx\n"
			"=A2	ecx\n"
			"=A3	edi\n"
			"gpr	eax	.32	0	0\n"
			"gpr	ecx	.32	4	0\n"
			"gpr	edx	.32	8	0\n"
			"gpr	ebx	.32	12	0\n"
			"gpr	esp	.32	16	0\n"
			"gpr	ebp	.32	20	0\n"
			"gpr	esi	.32	24	0\n"
			"gpr	edi	.32	28	0\n"
			"gpr	eip	.32	32	0\n"
			"gpr	eflags	.32	36	0\n"
			"seg	cs	.32	40	0\n"
			"seg	ss	.32	44	0\n"
			"seg	ds	.32	48	0\n"
			"seg	es	.32	52	0\n"
			"seg	fs	.32	56	0\n"
			"seg	gs	.32	60	0\n"
			);
		}
		break;
	case R_SYS_ARCH_ARM:
		if (bits == 64) {
			return strdup (
			"=PC	pc\n"
			"=SP	sp\n"
			"=BP	x29\n"
			"=A0	x0\n"
			"=A1	x1\n"
			"=A2	x2\n"
			"=A3	x3\n"
			"=ZF	zf\n"
			"=SF	nf\n"
			"=OF	vf\n"
			"=CF	cf\n"
			"=SN	x8\n"
			"gpr	x0	.64	0	0\n"
			"gpr	x1	.64	8	0\n"
			"gpr	x2	.64	16	0\n"
			"gpr	x3	.64	24	0\n"
			"gpr	x4	.64	32	0\n"
			"gpr	x5	.64	40	0\n"
			"gpr	x6	.64	48	0\n"
			"gpr	x7	.64	56	0\n"
			"gpr	x8	.64	64	0\n"
			"gpr	x9	.64	72	0\n"
			"gpr	x10	.64	80	0\n"
			"gpr	x11	.64	88	0\n"
			"gpr	x12	.64	96	0\n"
			"gpr	x13	.64	104	0\n"
			"gpr	x14	.64	112	0\n"
			"gpr	x15	.64	120	0\n"
			"gpr	x16	.64	128	0\n"
			"gpr	x17	.64	136	0\n"
			"gpr	x18	.64	144	0\n"
			"gpr	x19	.64	152	0\n"
			"gpr	x20	.64	160	0\n"
			"gpr	x21	.64	168	0\n"
			"gpr	x22	.64	176	0\n"
			"gpr	x23	.64	184	0\n"
			"gpr	x24	.64	192	0\n"
			"gpr	x25	.64	200	0\n"
			"gpr	x26	.64	208	0\n"
			"gpr	x27	.64	216	0\n"
			"gpr	x28	.64	224	0\n"
			"gpr	x29	.64	232	0\n"
			"gpr	x30	.64	240	0\n"
			"gpr	sp	.64	248	0\n"
			"gpr	pc	.64	256	0\n"
			"gpr	pstate	.64	264	0\n"
			);
		} else {
			return strdup (
#if 0
			"=PC	r15\n"
			"=SP	r14\n" // XXX
			"=A0	r0\n"
			"=A1	r1\n"
			"=A2	r2\n"
			"=A3	r3\n"
			"gpr	lr	.32	56	0\n" // r14
			"gpr	pc	.32	60	0\n" // r15
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
			"gpr	f0	.96	64	0\n"
			"gpr	f1	.96	76	0\n"
			"gpr	f2	.96	88	0\n"
			"gpr	f3	.96	100	0\n"
			"gpr	f4	.96	112	0\n"
			"gpr	f5	.96	124	0\n"
			"gpr	f6	.96	136	0\n"
			"gpr	f7	.96	148	0\n"
			"gpr	fps	.96	160	0\n"
			"gpr	cpsr	.32	172	0\n"
#else
			"=PC	pc\n"
			"=SP	sp\n"
			"=A0	r0\n"
			"=A1	r1\n"
			"=A2	r2\n"
			"=A3	r3\n"
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
			"gpr	sp	.32	52	0\n" // r13
			"gpr	lr	.32	56	0\n" // r14
			"gpr	pc	.32	60	0\n" // r15
			"gpr	r13	.32	52	0\n"
			"gpr	r14	.32	56	0\n"
			"gpr	r15	.32	60	0\n"
			"gpr	cpsr	.96	64	0\n"
			"mmx	d0	.64	68	0\n" // neon
			"mmx	d1	.64	76	0\n" // neon
			"mmx	d2	.64	84	0\n" // neon
			"mmx	d3	.64	92	0\n" // neon
			"mmx	d4	.64	100	0\n" // neon
			"mmx	d5	.64	108	0\n" // neon
			"mmx	d6	.64	116	0\n" // neon
			"mmx	d7	.64	124	0\n" // neon
			"mmx	d8	.64	132	0\n" // neon
			"mmx	d9	.64	140	0\n" // neon
			"mmx	d10	.64	148	0\n" // neon
			"mmx	d11	.64	156	0\n" // neon
			"mmx	d12	.64	164	0\n" // neon
			"mmx	d13	.64	172	0\n" // neon
			"mmx	d14	.64	180	0\n" // neon
			"mmx	d15	.64	188	0\n" // neon
			"mmx	d16	.64	196	0\n" // neon
			"mmx	d17	.64	204	0\n" // neon
			"mmx	d18	.64	212	0\n" // neon
			"mmx	d19	.64	220	0\n" // neon
			"mmx	d20	.64	228	0\n" // neon
			"mmx	d21	.64	236	0\n" // neon
			"mmx	d22	.64	244	0\n" // neon
			"mmx	d23	.64	252	0\n" // neon
			"mmx	d24	.64	260	0\n" // neon
			"mmx	d25	.64	268	0\n" // neon
			"mmx	d26	.64	276	0\n" // neon
			"mmx	d27	.64	284	0\n" // neon
			"mmx	d28	.64	292	0\n" // neon
			"mmx	d29	.64	300	0\n" // neon
			"mmx	d30	.64	308	0\n" // neon
			"mmx	d31	.64	316	0\n" // neon
			"mmx	fpscr	.32	324	0\n" // neon
#endif
			);
		}
		break;
	case R_SYS_ARCH_SH:
		return strdup (
			"=PC    pc\n"
			"=SP    r15\n"
			"=BP    r14\n"
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
			"gpr	mach	.32	80	0\n"
			"gpr	macl	.32	84	0\n"
		);
		break;
	case R_SYS_ARCH_LM32:
		return strdup (
			"=PC    PC\n"
			"=SP    sp\n"
			"=BP    gp\n"
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
			"gpr	r16	.32	64	0\n"
			"gpr	r17	.32	68	0\n"
			"gpr	r18	.32	72	0\n"
			"gpr	r19	.32	76	0\n"
			"gpr	r20	.32	80	0\n"
			"gpr	r21	.32	84	0\n"
			"gpr	r22	.32	88	0\n"
			"gpr	r23	.32	92	0\n"
			"gpr	r24	.32	96	0\n"
			"gpr	r25	.32	100	0\n"
			"gpr	gp	.32	104	0\n"
			"gpr	fp	.32	108	0\n"
			"gpr	sp	.32	112	0\n"
			"gpr	ra	.32	116	0\n"
			"gpr	ea	.32	120	0\n"
			"gpr	ba	.32	124	0\n"
			"gpr	PC	.32	128	0\n"
			"gpr	EID	.32	132	0\n"
			"gpr	EBA	.32	136	0\n"
			"gpr	DEBA	.32	140	0\n"
			"gpr	IE	.32	144	0\n"
			"gpr	IM	.32	148	0\n"
			"gpr	IP	.32	152	0\n"
		);
		break;
	case R_SYS_ARCH_MIPS:
		return strdup (
			"=PC    pc\n"
			"=SP    sp\n"
			"=BP    gp\n"
			"gpr	zero	.32	0	0\n"
			"gpr	at	.32	4	0\n"
			"gpr	v0	.32	8	0\n"
			"gpr	v1	.32	12	0\n"
			"gpr	a0	.32	16	0\n"
			"gpr	a1	.32	20	0\n"
			"gpr	a2	.32	24	0\n"
			"gpr	a3	.32	28	0\n"
			"gpr	t0	.32	32	0\n"
			"gpr	t1	.32	36	0\n"
			"gpr	t2	.32	40	0\n"
			"gpr	t3	.32	44	0\n"
			"gpr	t4	.32	48	0\n"
			"gpr	t5	.32	52	0\n"
			"gpr	t6	.32	56	0\n"
			"gpr	t7	.32	60	0\n"
			"gpr	s0	.32	64	0\n"
			"gpr	s1	.32	68	0\n"
			"gpr	s2	.32	72	0\n"
			"gpr	s3	.32	76	0\n"
			"gpr	s4	.32	80	0\n"
			"gpr	s5	.32	84	0\n"
			"gpr	s6	.32	88	0\n"
			"gpr	s7	.32	92	0\n"
			"gpr	t8	.32	96	0\n"
			"gpr	t9	.32	100	0\n"
			"gpr	k0	.32	104	0\n"
			"gpr	k1	.32	108	0\n"
			"gpr	gp	.32	112	0\n"
			"gpr	sp	.32	116	0\n"
			"gpr	s8	.32	120	0\n"
			"gpr	ra	.32	124	0\n"
			"gpr	sr	.32	128	0\n"
			"gpr	lo	.32	132	0\n"
			"gpr	hi	.32	134	0\n"
			"gpr	bad	.32	140	0\n"
			"gpr	cause	.32	144	0\n"
			"gpr	pc	.32	148	0\n"
			"gpr	f0	.32	152	0\n"
			"gpr	f1	.32	156	0\n"
			"gpr	f2	.32	160	0\n"
			"gpr	f3	.32	164	0\n"
			"gpr	f4	.32	168	0\n"
			"gpr	f5	.32	172	0\n"
			"gpr	f6	.32	176	0\n"
			"gpr	f7	.32	180	0\n"
			"gpr	f8	.32	184	0\n"
			"gpr	f9	.32	188	0\n"
			"gpr	f10	.32	192	0\n"
			"gpr	f11	.32	196	0\n"
			"gpr	f12	.32	200	0\n"
			"gpr	f13	.32	204	0\n"
			"gpr	f14	.32	208	0\n"
			"gpr	f15	.32	212	0\n"
			"gpr	f16	.32	216	0\n"
			"gpr	f17	.32	220	0\n"
			"gpr	f18	.32	224	0\n"
			"gpr	f19	.32	228	0\n"
			"gpr	f20	.32	232	0\n"
			"gpr	f21	.32	236	0\n"
			"gpr	f22	.32	240	0\n"
			"gpr	f23	.32	244	0\n"
			"gpr	f24	.32	248	0\n"
			"gpr	f25	.32	252	0\n"
			"gpr	f26	.32	256	0\n"
			"gpr	f27	.32	260	0\n"
			"gpr	f28	.32	264	0\n"
			"gpr	f29	.32	268	0\n"
			"gpr	f30	.32	272	0\n"
			"gpr	f31	.32	276	0\n"
			"gpr	fsr	.32	280	0\n"
			"gpr	fir	.32	284	0\n"
			"gpr	unknw	.32	288	0\n" //Not documented what this part of the register packet is
		);
	case R_SYS_ARCH_AVR:
		return strdup (
			"=PC    pc\n"
			"=SP    sp\n"
			"gpr	r0	.8	0	0\n"
			"gpr	r1	.8	1	0\n"
			"gpr	r2	.8	2	0\n"
			"gpr	r3	.8	3	0\n"
			"gpr	r4	.8	4	0\n"
			"gpr	r5	.8	5	0\n"
			"gpr	r6	.8	6	0\n"
			"gpr	r7	.8	7	0\n"
			"gpr	r8	.8	8	0\n"
			"gpr	r9	.8	9	0\n"
			"gpr	r10	.8	10	0\n"
			"gpr	r11	.8	11	0\n"
			"gpr	r12	.8	12	0\n"
			"gpr	r13	.8	13	0\n"
			"gpr	r14	.8	14	0\n"
			"gpr	r15	.8	15	0\n"
			"gpr	r16	.8	16	0\n"
			"gpr	r17	.8	17	0\n"
			"gpr	r18	.8	18	0\n"
			"gpr	r19	.8	19	0\n"
			"gpr	r20	.8	20	0\n"
			"gpr	r21	.8	21	0\n"
			"gpr	r22	.8	22	0\n"
			"gpr	r23	.8	23	0\n"
			"gpr	r24	.8	24	0\n"
			"gpr	r25	.8	25	0\n"
			"gpr	r26	.8	26	0\n"
			"gpr	r27	.8	27	0\n"
			"gpr	r28	.8	28	0\n"
			"gpr	r29	.8	29	0\n"
			"gpr	r30	.8	30	0\n"
			"gpr	r31	.8	31	0\n"
			"gpr	sreg	.8	32	0\n"
			"gpr	sp	.16	33	0\n"
			"gpr	pc2	.32	34	0\n"
			"gpr	pc	.32	35	0\n"
	/*		"gpr	pc	.32	39	0\n" */
	);
	case R_SYS_ARCH_V850:
		return strdup (
			"=PC    pc\n"
			"=SP    sp\n"
			"gpr	r0	.32	0	0\n"
			"gpr	r1	.32	4	0\n"
			"gpr	r2	.32	8	0\n"
			"gpr	sp	.32	12	0\n" // r3
			"gpr	gp	.32	16	0\n" // r4
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
			"gpr	r16	.32	64	0\n"
			"gpr	r17	.32	68	0\n"
			"gpr	r18	.32	72	0\n"
			"gpr	r19	.32	76	0\n"
			"gpr	r20	.32	80	0\n"
			"gpr	r21	.32	84	0\n"
			"gpr	r22	.32	88	0\n"
			"gpr	r23	.32	92	0\n"
			"gpr	r24	.32	96	0\n"
			"gpr	r25	.32	100	0\n"
			"gpr	r26	.32	104	0\n"
			"gpr	r27	.32	108	0\n"
			"gpr	r28	.32	112	0\n"
			"gpr	r29	.32	116	0\n"
			"gpr	ep	.32	120	0\n" // r30
			"gpr	lp	.32	124	0\n" // r31
			"gpr	eipc	.32	128	0\n"
			"gpr	eipsw	.32	132	0\n"
			"gpr	fepc	.32	136	0\n"
			"gpr	fepsw	.32	140	0\n"
			"gpr	ecr	.32	144	0\n"
			"gpr	psw	.32	148	0\n"
			// 5x reserved, sccfg, scbp, eiic, feic, dbic, ctpc, ctpsw, dbpc, dbpsw, ctbp
			// debug stuff, eiwr, fewr, dbwr, bsel
			"gpr	pc	.32	256	0\n"
	);
	}
	return NULL;
}