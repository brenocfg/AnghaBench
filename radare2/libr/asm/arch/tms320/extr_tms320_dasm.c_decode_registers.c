#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_5__ {int /*<<< orphan*/  syntax; } ;
typedef  TYPE_1__ tms320_dasm_t ;

/* Variables and functions */
 int /*<<< orphan*/  DD ; 
 int /*<<< orphan*/  DD2 ; 
 int /*<<< orphan*/  FDDD ; 
 int /*<<< orphan*/  FSSS ; 
 int /*<<< orphan*/  SS ; 
 int /*<<< orphan*/  SS2 ; 
 int /*<<< orphan*/  XACD ; 
 int /*<<< orphan*/  XACS ; 
 int /*<<< orphan*/  XDDD ; 
 int /*<<< orphan*/  XSSS ; 
 int /*<<< orphan*/  dd ; 
 scalar_t__ field_valid (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int field_value (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int get_freg_str (int,int /*<<< orphan*/ *) ; 
 int get_t_str (int,int /*<<< orphan*/ *) ; 
 int get_v_str (int,int /*<<< orphan*/ *) ; 
 int get_xreg_str (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r ; 
 int /*<<< orphan*/  ss ; 
 int /*<<< orphan*/  substitute (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  t ; 
 int /*<<< orphan*/  tt ; 
 int /*<<< orphan*/  vv ; 

void decode_registers(tms320_dasm_t * dasm)
{
	ut8 code = 0;

	// transition register

	if (field_valid (dasm, r)) {
		substitute (dasm->syntax, "TRNx", "trn%d", field_value (dasm, r));
	}

	// source and destination temporary registers

	if (field_valid (dasm, ss)) {
		substitute (dasm->syntax, "Tx", "t%d", field_value (dasm, ss));
	}

	if (field_valid (dasm, dd)) {
		substitute (dasm->syntax, "Tx", "t%d", field_value (dasm, dd));
	}

	// shifted in/out bit values

	if (field_valid(dasm, vv)) {
		substitute(dasm->syntax, "BitIn", "%s", get_v_str(field_value(dasm, vv) >> 1, NULL));
		substitute(dasm->syntax, "BitOut", "%s", get_v_str(field_value(dasm, vv) >> 0, NULL));
	}

	// source and destination of CRC instruction

	if (field_valid (dasm, t)) {
		substitute (dasm->syntax, "TCx", "%s", get_t_str (field_value (dasm, t), NULL));
	}

	if (field_valid(dasm, tt)) {
		substitute(dasm->syntax, "TCx", "%s", get_t_str(field_value(dasm, tt) >> 0, NULL));
		substitute(dasm->syntax, "TCy", "%s", get_t_str(field_value(dasm, tt) >> 1, NULL));
	}

	// source or destination accumulator or extended register

	if (field_valid(dasm, XSSS)) {
		substitute(dasm->syntax, "xsrc", "%s", get_xreg_str(field_value(dasm, XSSS), NULL));
		substitute(dasm->syntax, "XAsrc", "%s", get_xreg_str(field_value(dasm, XSSS), NULL));
	}

	if (field_valid(dasm, XDDD)) {
		substitute(dasm->syntax, "xdst", "%s", get_xreg_str(field_value(dasm, XDDD), NULL));
		substitute(dasm->syntax, "XAdst", "%s", get_xreg_str(field_value(dasm, XDDD), NULL));
	}

	// source or destination accumulator, auxiliary or temporary register

	if (field_valid(dasm, FSSS) && field_valid(dasm, FDDD)) {
		if (field_value (dasm, FSSS) == field_value (dasm, FDDD)) {
			substitute (dasm->syntax, "[src,] dst", "dst");
		} else {
			substitute (dasm->syntax, "[src,] dst", "src, dst");
		}
	}

	if (field_valid(dasm, FSSS) && field_valid(dasm, FDDD)) {
		substitute(dasm->syntax, "src1", "%s", get_freg_str(field_value(dasm, FSSS), NULL));
		substitute(dasm->syntax, "src2", "%s", get_freg_str(field_value(dasm, FDDD), NULL));

		substitute(dasm->syntax, "dst1", "%s", get_freg_str(field_value(dasm, FSSS), NULL));
		substitute(dasm->syntax, "dst2", "%s", get_freg_str(field_value(dasm, FDDD), NULL));
	}


	code &= 0;
	code |= field_valid(dasm, FSSS) ? 0x01 : 0x00;
	code |= field_valid(dasm, FDDD) ? 0x02 : 0x00;

	switch (code) {
	case 0x01:	// FSSS
		substitute(dasm->syntax, "TAx", "%s", get_freg_str(field_value(dasm, FSSS), NULL));
		break;
	case 0x02:	//      FDDD
		substitute(dasm->syntax, "TAx", "%s", get_freg_str(field_value(dasm, FDDD), NULL));
		substitute(dasm->syntax, "TAy", "%s", get_freg_str(field_value(dasm, FDDD), NULL));
		break;
	case 0x03:	// FSSS FDDD
		substitute(dasm->syntax, "TAx", "%s", get_freg_str(field_value(dasm, FSSS), NULL));
		substitute(dasm->syntax, "TAy", "%s", get_freg_str(field_value(dasm, FDDD), NULL));
		break;
	}

	if (field_valid(dasm, FSSS)) {
		substitute(dasm->syntax, "src", "%s", get_freg_str(field_value(dasm, FSSS), NULL));
	}

	if (field_valid(dasm, FDDD)) {
		substitute(dasm->syntax, "dst", "%s", get_freg_str(field_value(dasm, FDDD), NULL));
	}

	if (field_valid (dasm, XACS)) {
		substitute (dasm->syntax, "XACsrc", "%s", get_xreg_str (field_value (dasm, XACS), NULL));
	}

	if (field_valid (dasm, XACD)) {
		substitute (dasm->syntax, "XACdst", "%s", get_xreg_str (field_value (dasm, XACD), NULL));
	}

	// source and destination accumulator registers

	code &= 0;
	code |= field_valid(dasm, SS) ? 0x01 : 0x00;
	code |= field_valid(dasm, SS2) ? 0x02 : 0x00;
	code |= field_valid(dasm, DD) ? 0x10 : 0x00;
	code |= field_valid(dasm, DD2) ? 0x20 : 0x00;

	switch (code) {
	case 0x01:	// SS
		substitute(dasm->syntax, "ACx", "ac%d", field_value(dasm, SS));
		break;
	case 0x03:	// SSSS
		substitute(dasm->syntax, "ACx", "ac%d", field_value(dasm, SS));
		substitute(dasm->syntax, "ACy", "ac%d", field_value(dasm, SS2));
		break;
	case 0x11:	// SS   DD
		if (field_value(dasm, SS) == field_value(dasm, DD)) {
			substitute(dasm->syntax, "[, ACy]", "");
			substitute(dasm->syntax, "[ACx,] ACy", "ACy");
		} else {
			substitute(dasm->syntax, "[, ACy]", ", ACy");
			substitute(dasm->syntax, "[ACx,] ACy", "ACx, ACy");
		}
		substitute(dasm->syntax, "ACx", "ac%d", field_value(dasm, SS));
		substitute(dasm->syntax, "ACy", "ac%d", field_value(dasm, DD));
		break;
	case 0x33:	// SSSS DDDD
		substitute(dasm->syntax, "ACx", "ac%d", field_value(dasm, SS));
		substitute(dasm->syntax, "ACy", "ac%d", field_value(dasm, SS2));
		substitute(dasm->syntax, "ACz", "ac%d", field_value(dasm, DD));
		substitute(dasm->syntax, "ACw", "ac%d", field_value(dasm, DD2));
		break;
	case 0x10:	//      DD
		substitute(dasm->syntax, "ACx", "ac%d", field_value(dasm, DD));
		break;
	case 0x30:	//      DDDD
		substitute(dasm->syntax, "ACx", "ac%d", field_value(dasm, DD));
		substitute(dasm->syntax, "ACy", "ac%d", field_value(dasm, DD2));
		break;
	}
}