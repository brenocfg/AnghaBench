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
	const char *p = NULL;
	switch (anal->bits) {
	case 32: p =
		"=PC	pc\n"
		"=SP	sp\n" // ABI: stack pointer
		"=LR	ra\n" // ABI: return address
		"=BP	s0\n" // ABI: frame pointer

		"gpr	pc	.32	0	0\n"
		// RV32I regs (ABI names)
		// From user-Level ISA Specification, section 2.1
		// "zero" has been left out as it ignores writes and always reads as zero
		"gpr	ra	.32	4	0\n" // =x1
		"gpr	sp	.32	8	0\n" // =x2
		"gpr	gp	.32	12	0\n" // =x3
		"gpr	tp	.32	16	0\n" // =x4
		"gpr	t0	.32	20	0\n" // =x5
		"gpr	t1	.32	24	0\n" // =x6
		"gpr	t2	.32	28	0\n" // =x7
		"gpr	s0	.32	32	0\n" // =x8
		"gpr	s1	.32	36	0\n" // =x9
		"gpr	a0	.32	40	0\n" // =x10
		"gpr	a1	.32	44	0\n" // =x11
		"gpr	a2	.32	48	0\n" // =x12
		"gpr	a3	.32	52	0\n" // =x13
		"gpr	a4	.32	56	0\n" // =x14
		"gpr	a5	.32	60	0\n" // =x15
		"gpr	a6	.32	64	0\n" // =x16
		"gpr	a7	.32	68	0\n" // =x17
		"gpr	s2	.32	72	0\n" // =x18
		"gpr	s3	.32	76	0\n" // =x19
		"gpr	s4	.32	80	0\n" // =x20
		"gpr	s5	.32	84	0\n" // =x21
		"gpr	s6	.32	88	0\n" // =x22
		"gpr	s7	.32	92	0\n" // =x23
		"gpr	s8	.32	96	0\n" // =x24
		"gpr	s9	.32	100	0\n" // =x25
		"gpr	s10	.32	104	0\n" // =x26
		"gpr	s11	.32	108	0\n" // =x27
		"gpr	t3	.32	112	0\n" // =x28
		"gpr	t4	.32	116	0\n" // =x29
		"gpr	t5	.32	120	0\n" // =x30
		"gpr	t6	.32	124	0\n" // =x31
		// RV32F/D regs (ABI names)
		// From user-Level ISA Specification, section 8.1 and 9.1
		"gpr	ft0	.64	128	0\n" // =f0
		"gpr	ft1	.64	136	0\n" // =f1
		"gpr	ft2	.64	144	0\n" // =f2
		"gpr	ft3	.64	152	0\n" // =f3
		"gpr	ft4	.64	160	0\n" // =f4
		"gpr	ft5	.64	168	0\n" // =f5
		"gpr	ft6	.64	176	0\n" // =f6
		"gpr	ft7	.64	184	0\n" // =f7
		"gpr	fs0	.64	192	0\n" // =f8
		"gpr	fs1	.64	200	0\n" // =f9
		"gpr	fa0	.64	208	0\n" // =f10
		"gpr	fa1	.64	216	0\n" // =f11
		"gpr	fa2	.64	224	0\n" // =f12
		"gpr	fa3	.64	232	0\n" // =f13
		"gpr	fa4	.64	240	0\n" // =f14
		"gpr	fa5	.64	248	0\n" // =f15
		"gpr	fa6	.64	256	0\n" // =f16
		"gpr	fa7	.64	264	0\n" // =f17
		"gpr	fs2	.64	272	0\n" // =f18
		"gpr	fs3	.64	280	0\n" // =f19
		"gpr	fs4	.64	288	0\n" // =f20
		"gpr	fs5	.64	296	0\n" // =f21
		"gpr	fs6	.64	304	0\n" // =f22
		"gpr	fs7	.64	312	0\n" // =f23
		"gpr	fs8	.64	320	0\n" // =f24
		"gpr	fs9	.64	328	0\n" // =f25
		"gpr	fs10	.64	336	0\n" // =f26
		"gpr	fs11	.64	344	0\n" // =f27
		"gpr	ft8	.64	352	0\n" // =f28
		"gpr	ft9	.64	360	0\n" // =f29
		"gpr	ft10	.64	368	0\n" // =f30
		"gpr	ft11	.64	376	0\n" // =f31
		"gpr	fcsr	.32	384	0\n"
		"flg	nx	.1	3072	0\n"
		"flg	uf	.1	3073	0\n"
		"flg	of	.1	3074	0\n"
		"flg	dz	.1	3075	0\n"
		"flg	nv	.1	3076	0\n"
		"flg	frm	.3	3077	0\n"
		;

		break;
	case 64: p =
		"=PC	pc\n"
		"=SP	sp\n" // ABI: stack pointer
		"=LR	ra\n" // ABI: return address
		"=BP	s0\n" // ABI: frame pointer

		"gpr	pc	.64	0	0\n"
		// RV64I regs (ABI names)
		// From user-Level ISA Specification, section 2.1 and 4.1
		// "zero" has been left out as it ignores writes and always reads as zero
		"gpr	ra	.64	8	0\n" // =x1
		"gpr	sp	.64	16	0\n" // =x2
		"gpr	gp	.64	24	0\n" // =x3
		"gpr	tp	.64	32	0\n" // =x4
		"gpr	t0	.64	40	0\n" // =x5
		"gpr	t1	.64	48	0\n" // =x6
		"gpr	t2	.64	56	0\n" // =x7
		"gpr	s0	.64	64	0\n" // =x8
		"gpr	s1	.64	72	0\n" // =x9
		"gpr	a0	.64	80	0\n" // =x10
		"gpr	a1	.64	88	0\n" // =x11
		"gpr	a2	.64	96	0\n" // =x12
		"gpr	a3	.64	104	0\n" // =x13
		"gpr	a4	.64	112	0\n" // =x14
		"gpr	a5	.64	120	0\n" // =x15
		"gpr	a6	.64	128	0\n" // =x16
		"gpr	a7	.64	136	0\n" // =x17
		"gpr	s2	.64	144	0\n" // =x18
		"gpr	s3	.64	152	0\n" // =x19
		"gpr	s4	.64	160	0\n" // =x20
		"gpr	s5	.64	168	0\n" // =x21
		"gpr	s6	.64	176	0\n" // =x22
		"gpr	s7	.64	184	0\n" // =x23
		"gpr	s8	.64	192	0\n" // =x24
		"gpr	s9	.64	200	0\n" // =x25
		"gpr	s10	.64	208	0\n" // =x26
		"gpr	s11	.64	216	0\n" // =x27
		"gpr	t3	.64	224	0\n" // =x28
		"gpr	t4	.64	232	0\n" // =x29
		"gpr	t5	.64	240	0\n" // =x30
		"gpr	t6	.64	248	0\n" // =x31
		// RV64F/D regs (ABI names)
		"gpr	ft0	.64	256	0\n" // =f0
		"gpr	ft1	.64	264	0\n" // =f1
		"gpr	ft2	.64	272	0\n" // =f2
		"gpr	ft3	.64	280	0\n" // =f3
		"gpr	ft4	.64	288	0\n" // =f4
		"gpr	ft5	.64	296	0\n" // =f5
		"gpr	ft6	.64	304	0\n" // =f6
		"gpr	ft7	.64	312	0\n" // =f7
		"gpr	fs0	.64	320	0\n" // =f8
		"gpr	fs1	.64	328	0\n" // =f9
		"gpr	fa0	.64	336	0\n" // =f10
		"gpr	fa1	.64	344	0\n" // =f11
		"gpr	fa2	.64	352	0\n" // =f12
		"gpr	fa3	.64	360	0\n" // =f13
		"gpr	fa4	.64	368	0\n" // =f14
		"gpr	fa5	.64	376	0\n" // =f15
		"gpr	fa6	.64	384	0\n" // =f16
		"gpr	fa7	.64	392	0\n" // =f17
		"gpr	fs2	.64	400	0\n" // =f18
		"gpr	fs3	.64	408	0\n" // =f19
		"gpr	fs4	.64	416	0\n" // =f20
		"gpr	fs5	.64	424	0\n" // =f21
		"gpr	fs6	.64	432	0\n" // =f22
		"gpr	fs7	.64	440	0\n" // =f23
		"gpr	fs8	.64	448	0\n" // =f24
		"gpr	fs9	.64	456	0\n" // =f25
		"gpr	fs10	.64	464	0\n" // =f26
		"gpr	fs11	.64	472	0\n" // =f27
		"gpr	ft8	.64	480	0\n" // =f28
		"gpr	ft9	.64	488	0\n" // =f29
		"gpr	ft10	.64	496	0\n" // =f30
		"gpr	ft11	.64	504	0\n" // =f31
		"gpr	fcsr	.32	512	0\n"
		"flg	nx	.1	4096	0\n"
		"flg	uf	.1	4097	0\n"
		"flg	of	.1	4098	0\n"
		"flg	dz	.1	4099	0\n"
		"flg	nv	.1	4100	0\n"
		"flg	frm	.3	4101	0\n"
		;

		break;
	}
	return (p && *p)? strdup (p): NULL;
}