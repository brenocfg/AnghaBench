#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ RAnal ;

/* Variables and functions */
 int r_reg_set_profile_string (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  set_cpu_model (TYPE_1__*,int) ; 

__attribute__((used)) static int set_reg_profile(RAnal *anal) {
	const char *p =
		"=PC	pc\n"
		"=SP	sp\n"
		"gpr	r0	.8	0	0\n"
		"gpr	r1	.8	1	0\n"
		"gpr	r2	.8	2	0\n"
		"gpr	r3	.8	3	0\n"
		"gpr	r4	.8	4	0\n"
		"gpr	r5	.8	5	0\n"
		"gpr	r6	.8	6	0\n"
		"gpr	r7	.8	7	0\n"
		"gpr	a	.8	8	0\n"
		"gpr	b	.8	9	0\n"
		"gpr	dptr	.16	10	0\n"
		"gpr	dpl	.8	10	0\n"
		"gpr	dph	.8	11	0\n"
		"gpr	psw	.8	12	0\n"
		"gpr	p	.1	.96	0\n"
		"gpr	ov	.1	.98	0\n"
		"gpr	ac	.1	.102	0\n"
		"gpr	c	.1	.103	0\n"
		"gpr	sp	.8	13	0\n"
		"gpr	pc	.16	15	0\n"
// ---------------------------------------------------
// 8051 memory emulation control registers
// These registers map 8051 memory classes to r2's
// linear address space. Registers contain base addr
// in r2 memory space representing the memory class.
// Offsets are initialized based on asm.cpu, but can
// be updated with ar command.
//
// _code
//		program memory (CODE)
// _idata
//		internal data memory (IDATA, IRAM)
// _sfr
//		special function registers (SFR)
// _xdata
//		external data memory (XDATA, XRAM)
// _pdata
//		page accessed by movx @ri op (PDATA, XREG)
//		r2 addr = (_pdata & 0xff) << 8 + x_data
//		if 0xffffffnn, addr = ([SFRnn] << 8) + _xdata (TODO)
		"gpr	_code	.32	20 0\n"
		"gpr	_idata	.32 24 0\n"
		"gpr	_sfr	.32	28 0\n"
		"gpr	_xdata	.32 32 0\n"
		"gpr	_pdata	.32	36 0\n";

	int retval = r_reg_set_profile_string (anal->reg, p);
	if (retval) {
		// reset emulation control registers based on cpu
		set_cpu_model (anal, true);
	}

	return retval;
}