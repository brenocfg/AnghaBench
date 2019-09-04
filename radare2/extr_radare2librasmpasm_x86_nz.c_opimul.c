#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int st64 ;
struct TYPE_9__ {int operands_count; TYPE_1__* operands; } ;
struct TYPE_8__ {int bits; } ;
struct TYPE_7__ {int type; int* regs; int reg; int immediate; int sign; int offset; int offset_sign; } ;
typedef  TYPE_2__ RAsm ;
typedef  TYPE_3__ Opcode ;

/* Variables and functions */
 int OT_BYTE ; 
 int OT_CONSTANT ; 
 int OT_GPREG ; 
 int OT_MEMORY ; 
 int OT_QWORD ; 
 int OT_WORD ; 
 int UT32_MAX ; 
 int X86R_UNDEFINED ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  is_valid_registers (TYPE_3__ const*) ; 

__attribute__((used)) static int opimul(RAsm *a, ut8 *data, const Opcode *op) {
	is_valid_registers (op);
	int l = 0;
	int offset = 0;
	st64 immediate = 0;

	if ( op->operands[0].type & OT_QWORD ) {
		data[l++] = 0x48;
	}
	switch (op->operands_count) {
	case 1:
		if ( op->operands[0].type & OT_WORD ) {
			data[l++] = 0x66;
		}
		if (op->operands[0].type & OT_BYTE) {
			data[l++] = 0xf6;
		} else {
			data[l++] = 0xf7;
		}
		if (op->operands[0].type & OT_MEMORY) {
			data[l++] = 0x28 | op->operands[0].regs[0];
		} else {
			data[l++] = 0xe8 | op->operands[0].reg;
		}
		break;
	case 2:
		if (op->operands[0].type & OT_GPREG) {
			if (op->operands[1].type & OT_CONSTANT) {
				if (op->operands[1].immediate == -1) {
					eprintf ("Error: Immediate exceeds max\n");
					return -1;
				}
				immediate = op->operands[1].immediate * op->operands[1].sign;
				if (op->operands[0].type & OT_GPREG) {
					if (immediate >= 128) {
						data[l++] = 0x69;
					} else {
						data[l++] = 0x6b;
					}
					data[l++] = 0xc0 | op->operands[0].reg << 3 | op->operands[0].reg;
					data[l++] = immediate;
					if (immediate >= 128) {
						data[l++] = immediate >> 8;
						data[l++] = immediate >> 16;
						data[l++] = immediate >> 24;
					}
					if (a->bits == 64 && immediate > UT32_MAX) {
						data[l++] = immediate >> 32;
						data[l++] = immediate >> 40;
						data[l++] = immediate >> 48;
						data[l++] = immediate >> 56;
					}
				}
			} else if (op->operands[1].type & OT_MEMORY) {
				data[l++] = 0x0f;
				data[l++] = 0xaf;
				if (op->operands[1].regs[0] != X86R_UNDEFINED) {
					offset = op->operands[1].offset * op->operands[1].offset_sign;
					if (offset != 0) {
						if (offset >= 128 || offset <= -128) {
							data[l] = 0x80;
						} else {
							data[l] = 0x40;
						}
						data[l++] |= op->operands[0].reg << 3 | op->operands[1].regs[0];
						data[l++] = offset;
						if (offset >= 128 || offset <= -128) {
							data[l++] = offset >> 8;
							data[l++] = offset >> 16;
							data[l++] = offset >> 24;
						}
					} else {
						if (op->operands[1].regs[1] != X86R_UNDEFINED) {
							data[l++] = 0x04 | op->operands[0].reg << 3;
							data[l++] = op->operands[1].regs[1] << 3 | op->operands[1].regs[0];
						} else {
							data[l++] = op->operands[0].reg << 3 | op->operands[1].regs[0];
						}
					}
				} else {
					immediate = op->operands[1].immediate * op->operands[1].sign;
					data[l++] = op->operands[0].reg << 3 | 0x5;
					data[l++] = immediate;
					data[l++] = immediate >> 8;
					data[l++] = immediate >> 16;
					data[l++] = immediate >> 24;
				}
			} else if (op->operands[1].type & OT_GPREG) {
				data[l++] = 0x0f;
				data[l++] = 0xaf;
				data[l++] = 0xc0 | op->operands[0].reg << 3 | op->operands[1].reg;
			}
		}
		break;
	case 3:
		if (op->operands[0].type & OT_GPREG &&
		    (op->operands[1].type & OT_GPREG || op->operands[1].type & OT_MEMORY) &&
		    op->operands[2].type & OT_CONSTANT) {
				data[l++] = 0x6b;
				if (op->operands[1].type & OT_MEMORY) {
					if (op->operands[1].regs[1] != X86R_UNDEFINED) {
						data[l++] = 0x04 | op->operands[0].reg << 3;
						data[l++] = op->operands[1].regs[0] |  op->operands[1].regs[1] << 3;
					} else {
						offset = op->operands[1].offset * op->operands[1].offset_sign;
						if (offset != 0) {
							if (offset >= 128 || offset <= -128) {
								data[l] = 0x80;
							} else {
								data[l] = 0x40;
							}
							data[l++] |= op->operands[0].reg << 3;
							data[l++] = offset;
							if (offset >= 128 || offset <= -128) {
								data[l++] = offset >> 8;
								data[l++] = offset >> 16;
								data[l++] = offset >> 24;
							}
						} else {
							data[l++] = 0x00 | op->operands[0].reg << 3 | op->operands[1].regs[0];
						}
					}
				} else {
					data[l++] = 0xc0 | op->operands[0].reg << 3 | op->operands[1].reg;
				}
				immediate = op->operands[2].immediate * op->operands[2].sign;
				data[l++] = immediate;
				if (immediate >= 128 || immediate <= -128) {
					data[l++] = immediate >> 8;
					data[l++] = immediate >> 16;
					data[l++] = immediate >> 24;
				}
		}
		break;
	default:
		return -1;
	}
	return l;
}