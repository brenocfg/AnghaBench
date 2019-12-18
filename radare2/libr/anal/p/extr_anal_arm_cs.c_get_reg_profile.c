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
struct TYPE_3__ {int bits; } ;
typedef  TYPE_1__ RAnal ;

/* Variables and functions */
 char* strdup (char const*) ; 

__attribute__((used)) static char *get_reg_profile(RAnal *anal) {
	const char *p;
	if (anal->bits == 64) {
		p = \
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
		"=SN	x16\n" // x8 on linux?

		/* 8bit sub-registers */
		"gpr	b0	.8	0	0\n"
		"gpr	b1	.8	8	0\n"
		"gpr	b2	.8	16	0\n"
		"gpr	b3	.8	24	0\n"
		"gpr	b4	.8	32	0\n"
		"gpr	b5	.8	40	0\n"
		"gpr	b6	.8	48	0\n"
		"gpr	b7	.8	56	0\n"
		"gpr	b8	.8	64	0\n"
		"gpr	b9	.8	72	0\n"
		"gpr	b10	.8	80	0\n"
		"gpr	b11	.8	88	0\n"
		"gpr	b12	.8	96	0\n"
		"gpr	b13	.8	104	0\n"
		"gpr	b14	.8	112	0\n"
		"gpr	b15	.8	120	0\n"
		"gpr	b16	.8	128	0\n"
		"gpr	b17	.8	136	0\n"
		"gpr	b18	.8	144	0\n"
		"gpr	b19	.8	152	0\n"
		"gpr	b20	.8	160	0\n"
		"gpr	b21	.8	168	0\n"
		"gpr	b22	.8	176	0\n"
		"gpr	b23	.8	184	0\n"
		"gpr	b24	.8	192	0\n"
		"gpr	b25	.8	200	0\n"
		"gpr	b26	.8	208	0\n"
		"gpr	b27	.8	216	0\n"
		"gpr	b28	.8	224	0\n"
		"gpr	b29	.8	232	0\n"
		"gpr	b30	.8	240	0\n"
		"gpr	bsp	.8	248	0\n"

		/* 16bit sub-registers */
		"gpr	h0	.16	0	0\n"
		"gpr	h1	.16	8	0\n"
		"gpr	h2	.16	16	0\n"
		"gpr	h3	.16	24	0\n"
		"gpr	h4	.16	32	0\n"
		"gpr	h5	.16	40	0\n"
		"gpr	h6	.16	48	0\n"
		"gpr	h7	.16	56	0\n"
		"gpr	h8	.16	64	0\n"
		"gpr	h9	.16	72	0\n"
		"gpr	h10	.16	80	0\n"
		"gpr	h11	.16	88	0\n"
		"gpr	h12	.16	96	0\n"
		"gpr	h13	.16	104	0\n"
		"gpr	h14	.16	112	0\n"
		"gpr	h15	.16	120	0\n"
		"gpr	h16	.16	128	0\n"
		"gpr	h17	.16	136	0\n"
		"gpr	h18	.16	144	0\n"
		"gpr	h19	.16	152	0\n"
		"gpr	h20	.16	160	0\n"
		"gpr	h21	.16	168	0\n"
		"gpr	h22	.16	176	0\n"
		"gpr	h23	.16	184	0\n"
		"gpr	h24	.16	192	0\n"
		"gpr	h25	.16	200	0\n"
		"gpr	h26	.16	208	0\n"
		"gpr	h27	.16	216	0\n"
		"gpr	h28	.16	224	0\n"
		"gpr	h29	.16	232	0\n"
		"gpr	h30	.16	240	0\n"

		/* 32bit sub-registers */
		"gpr	w0	.32	0	0\n"
		"gpr	w1	.32	8	0\n"
		"gpr	w2	.32	16	0\n"
		"gpr	w3	.32	24	0\n"
		"gpr	w4	.32	32	0\n"
		"gpr	w5	.32	40	0\n"
		"gpr	w6	.32	48	0\n"
		"gpr	w7	.32	56	0\n"
		"gpr	w8	.32	64	0\n"
		"gpr	w9	.32	72	0\n"
		"gpr	w10	.32	80	0\n"
		"gpr	w11	.32	88	0\n"
		"gpr	w12	.32	96	0\n"
		"gpr	w13	.32	104	0\n"
		"gpr	w14	.32	112	0\n"
		"gpr	w15	.32	120	0\n"
		"gpr	w16	.32	128	0\n"
		"gpr	w17	.32	136	0\n"
		"gpr	w18	.32	144	0\n"
		"gpr	w19	.32	152	0\n"
		"gpr	w20	.32	160	0\n"
		"gpr	w21	.32	168	0\n"
		"gpr	w22	.32	176	0\n"
		"gpr	w23	.32	184	0\n"
		"gpr	w24	.32	192	0\n"
		"gpr	w25	.32	200	0\n"
		"gpr	w26	.32	208	0\n"
		"gpr	w27	.32	216	0\n"
		"gpr	w28	.32	224	0\n"
		"gpr	w29	.32	232	0\n"
		"gpr	w30	.32	240	0\n"
		"gpr	wsp	.32	248	0\n"
		"gpr	wzr	.32	?	0\n"

		/* 32bit float sub-registers */
		"gpr	s0	.32	0	0\n"
		"gpr	s1	.32	8	0\n"
		"gpr	s2	.32	16	0\n"
		"gpr	s3	.32	24	0\n"
		"gpr	s4	.32	32	0\n"
		"gpr	s5	.32	40	0\n"
		"gpr	s6	.32	48	0\n"
		"gpr	s7	.32	56	0\n"
		"gpr	s8	.32	64	0\n"
		"gpr	s9	.32	72	0\n"
		"gpr	s10	.32	80	0\n"
		"gpr	s11	.32	88	0\n"
		"gpr	s12	.32	96	0\n"
		"gpr	s13	.32	104	0\n"
		"gpr	s14	.32	112	0\n"
		"gpr	s15	.32	120	0\n"
		"gpr	s16	.32	128	0\n"
		"gpr	s17	.32	136	0\n"
		"gpr	s18	.32	144	0\n"
		"gpr	s19	.32	152	0\n"
		"gpr	s20	.32	160	0\n"
		"gpr	s21	.32	168	0\n"
		"gpr	s22	.32	176	0\n"
		"gpr	s23	.32	184	0\n"
		"gpr	s24	.32	192	0\n"
		"gpr	s25	.32	200	0\n"
		"gpr	s26	.32	208	0\n"
		"gpr	s27	.32	216	0\n"
		"gpr	s28	.32	224	0\n"
		"gpr	s29	.32	232	0\n"
		"gpr	s30	.32	240	0\n"
		/* 64bit */
		"gpr	x0	.64	0	0\n" // x0
		"gpr	x1	.64	8	0\n" // x0
		"gpr	x2	.64	16	0\n" // x0
		"gpr	x3	.64	24	0\n" // x0
		"gpr	x4	.64	32	0\n" // x0
		"gpr	x5	.64	40	0\n" // x0
		"gpr	x6	.64	48	0\n" // x0
		"gpr	x7	.64	56	0\n" // x0
		"gpr	x8	.64	64	0\n" // x0
		"gpr	x9	.64	72	0\n" // x0
		"gpr	x10	.64	80	0\n" // x0
		"gpr	x11	.64	88	0\n" // x0
		"gpr	x12	.64	96	0\n" // x0
		"gpr	x13	.64	104	0\n" // x0
		"gpr	x14	.64	112	0\n" // x0
		"gpr	x15	.64	120	0\n" // x0
		"gpr	x16	.64	128	0\n" // x0
		"gpr	x17	.64	136	0\n" // x0
		"gpr	x18	.64	144	0\n" // x0
		"gpr	x19	.64	152	0\n" // x0
		"gpr	x20	.64	160	0\n" // x0
		"gpr	x21	.64	168	0\n" // x0
		"gpr	x22	.64	176	0\n" // x0
		"gpr	x23	.64	184	0\n" // x0
		"gpr	x24	.64	192	0\n" // x0
		"gpr	x25	.64	200	0\n" // x0
		"gpr	x26	.64	208	0\n" // x0
		"gpr	x27	.64	216	0\n"
		"gpr	x28	.64	224	0\n"
		"gpr	x29	.64	232	0\n"
		"gpr	x30	.64	240	0\n"
		"gpr	tmp	.64	288	0\n"
		/* 64bit double */
		"gpr	d0	.64	0	0\n" // x0
		"gpr	d1	.64	8	0\n" // x0
		"gpr	d2	.64	16	0\n" // x0
		"gpr	d3	.64	24	0\n" // x0
		"gpr	d4	.64	32	0\n" // x0
		"gpr	d5	.64	40	0\n" // x0
		"gpr	d6	.64	48	0\n" // x0
		"gpr	d7	.64	56	0\n" // x0
		"gpr	d8	.64	64	0\n" // x0
		"gpr	d9	.64	72	0\n" // x0
		"gpr	d10	.64	80	0\n" // x0
		"gpr	d11	.64	88	0\n" // x0
		"gpr	d12	.64	96	0\n" // x0
		"gpr	d13	.64	104	0\n" // x0
		"gpr	d14	.64	112	0\n" // x0
		"gpr	d15	.64	120	0\n" // x0
		"gpr	d16	.64	128	0\n" // x0
		"gpr	d17	.64	136	0\n" // x0
		"gpr	d18	.64	144	0\n" // x0
		"gpr	d19	.64	152	0\n" // x0
		"gpr	d20	.64	160	0\n" // x0
		"gpr	d21	.64	168	0\n" // x0
		"gpr	d22	.64	176	0\n" // x0
		"gpr	d23	.64	184	0\n" // x0
		"gpr	d24	.64	192	0\n" // x0
		"gpr	d25	.64	200	0\n" // x0
		"gpr	d26	.64	208	0\n" // x0
		"gpr	d27	.64	216	0\n"
		"gpr	d28	.64	224	0\n"
		"gpr	d29	.64	232	0\n"
		"gpr	d30	.64	240	0\n"
		"gpr	dsp	.64	248	0\n"
		/*  foo */
		"gpr	fp	.64	232	0\n" // fp = x29
		"gpr	lr	.64	240	0\n" // lr = x30
		"gpr	sp	.64	248	0\n"
		"gpr	pc	.64	256	0\n"
		"gpr	zr	.64	?	0\n"
		"gpr	xzr	.64	?	0\n"
		"flg	pstate	.64	280	0   _____tfiae_____________j__qvczn\n" // x0
		//"flg	cpsr	.32	280	0\n" //	_____tfiae_____________j__qvczn\n"
		"flg	vf	.1	280.28	0	overflow\n" // set if overflows
		"flg	cf	.1	280.29	0	carry\n" // set if last op carries
		"flg	zf	.1	280.30	0	zero\n" // set if last op is 0
		"flg	nf	.1	280.31	0	sign\n"; // msb bit of last op
	} else {
		p = \
		"=PC	r15\n"
		"=LR	r14\n"
		"=SP	sp\n"
		"=BP	fp\n"
		"=A0	r0\n"
		"=A1	r1\n"
		"=A2	r2\n"
		"=A3	r3\n"
		"=ZF	zf\n"
		"=SF	nf\n"
		"=OF	vf\n"
		"=CF	cf\n"
		"=SN	r7\n"
		"gpr	sb	.32	36	0\n" // r9
		"gpr	sl	.32	40	0\n" // rl0
		"gpr	fp	.32	44	0\n" // r11
		"gpr	ip	.32	48	0\n" // r12
		"gpr	sp	.32	52	0\n" // r13
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
		"flg	cpsr	.32	64	0\n"
		"gpr	blank	.32	68	0\n" // Hack, the bit fields below don't work on the last register??

		  // CPSR bit fields:
		  // 576-580 Mode fields (and register sets associated to each field):
		  //10000 	User 	R0-R14, CPSR, PC
		  //10001 	FIQ 	R0-R7, R8_fiq-R14_fiq, CPSR, SPSR_fiq, PC
		  //10010 	IRQ 	R0-R12, R13_irq, R14_irq, CPSR, SPSR_irq, PC
		  //10011 	SVC (supervisor) 	R0-R12, R13_svc R14_svc CPSR, SPSR_irq, PC
		  //10111 	Abort 	R0-R12, R13_abt R14_abt CPSR, SPSR_abt PC
		  //11011 	Undefined 	R0-R12, R13_und R14_und, CPSR, SPSR_und PC
		  //11111 	System (ARMv4+) 	R0-R14, CPSR, PC
		"flg	tf	.1	.517	0	thumb\n" // +5
		  // 582 FIQ disable bit
		  // 583 IRQ disable bit
		  // 584 Disable imprecise aborts flag
		"flg	ef	.1	.521	0	endian\n" // +9
		"flg	itc	.4	.522	0	if_then_count\n" // +10
		  // Reserved
		"flg	gef	.4	.528	0	great_or_equal\n" // +16
		"flg	jf	.1	.536	0	java\n" // +24
		  // Reserved
		"flg	qf	.1	.539	0	sticky_overflow\n" // +27
		"flg	vf	.1	.540	0	overflow\n" // +28
		"flg	cf	.1	.541	0	carry\n" // +29
		"flg	zf	.1	.542	0	zero\n" // +30
		"flg	nf	.1	.543	0	negative\n" // +31
		;
	}
	return strdup (p);
}