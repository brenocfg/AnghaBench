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
struct TYPE_9__ {int is_short; int /*<<< orphan*/  mnemonic; TYPE_1__* operands; } ;
struct TYPE_8__ {int bits; scalar_t__ pc; } ;
struct TYPE_7__ {int immediate; int sign; int type; int offset; int offset_sign; int* regs; int reg; } ;
typedef  TYPE_2__ RAsm ;
typedef  TYPE_3__ Opcode ;

/* Variables and functions */
 int OT_GPREG ; 
 int OT_MEMORY ; 
 int ST32_MAX ; 
 int ST8_MAX ; 
 int ST8_MIN ; 
 int X86R_ESP ; 
 int /*<<< orphan*/  is_valid_registers (TYPE_3__ const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int opjc(RAsm *a, ut8 *data, const Opcode *op) {
	is_valid_registers (op);
	int l = 0;
	bool is_short = op->is_short;
	// st64 bigimm = op->operands[0].immediate * op->operands[0].sign;
	st64 immediate = op->operands[0].immediate * op->operands[0].sign;
	if (is_short && (immediate > ST8_MAX || immediate < ST8_MIN)) {
		return l;
	}
	immediate -= a->pc;
	if (immediate > ST32_MAX || immediate < -ST32_MAX) {
		return -1;
	}
	if (!strcmp (op->mnemonic, "jmp")) {
		if (op->operands[0].type & OT_GPREG) {
			data[l++] = 0xff;
			if (op->operands[0].type & OT_MEMORY) {
				if (op->operands[0].offset) {
					int offset = op->operands[0].offset * op->operands[0].offset_sign;
					if (offset >= 128 || offset <= -129) {
						data[l] = 0xa0;
					} else {
						data[l] = 0x60;
					}
					data[l++] |= op->operands[0].regs[0];
					if (op->operands[0].regs[0] == X86R_ESP) {
						data[l++] = 0x24;
					}
					data[l++] = offset;
					if (op->operands[0].offset >= 0x80) {
						data[l++] = offset >> 8;
						data[l++] = offset >> 16;
						data[l++] = offset >> 24;
					}
				} else {
					data[l++] = 0x20 | op->operands[0].regs[0];
				}
			} else {
				data[l++] = 0xe0 | op->operands[0].reg;
			}
		} else {
			if (-0x80 <= (immediate - 2) && (immediate - 2) <= 0x7f) {
				/* relative byte address */
				data[l++] = 0xeb;
				data[l++] = immediate - 2;
			} else {
				/* relative address */
				immediate -= 5;
				data[l++] = 0xe9;
				data[l++] = immediate;
				data[l++] = immediate >> 8;
				data[l++] = immediate >> 16;
				data[l++] = immediate >> 24;
			}
		}
		return l;
	}
	if (immediate <= 0x81 && immediate > -0x7f) {
		is_short = true;
	}
	if (a->bits == 16 && (immediate > 0x81 || immediate < -0x7e)) {
		data[l++] = 0x66;
		is_short = false;
		immediate --;
	}

	if (!is_short) {data[l++] = 0x0f;}
	if (!strcmp (op->mnemonic, "ja") ||
            !strcmp (op->mnemonic, "jnbe")) {
		data[l++] = 0x87;
	} else if (!strcmp (op->mnemonic, "jae") ||
                   !strcmp (op->mnemonic, "jnb") ||
                   !strcmp (op->mnemonic, "jnc")) {
		data[l++] = 0x83;
	} else if (!strcmp (op->mnemonic, "jz") ||
                   !strcmp (op->mnemonic, "je")) {
		data[l++] = 0x84;
	} else if (!strcmp (op->mnemonic, "jb") ||
                   !strcmp (op->mnemonic, "jnae") ||
                   !strcmp (op->mnemonic, "jc")) {
		data[l++] = 0x82;
	} else if (!strcmp (op->mnemonic, "jbe") ||
                   !strcmp (op->mnemonic, "jna")) {
		data[l++] = 0x86;
	} else if (!strcmp (op->mnemonic, "jg") ||
                   !strcmp (op->mnemonic, "jnle")) {
		data[l++] = 0x8f;
	} else if (!strcmp (op->mnemonic, "jge") ||
                   !strcmp (op->mnemonic, "jnl")) {
		data[l++] = 0x8d;
	} else if (!strcmp (op->mnemonic, "jl") ||
                   !strcmp (op->mnemonic, "jnge")) {
		data[l++] = 0x8c;
	} else if (!strcmp (op->mnemonic, "jle") ||
	           !strcmp (op->mnemonic, "jng")) {
		data[l++] = 0x8e;
	} else if (!strcmp (op->mnemonic, "jne") ||
                   !strcmp (op->mnemonic, "jnz")) {
		data[l++] = 0x85;
	} else if (!strcmp (op->mnemonic, "jno")) {
		data[l++] = 0x81;
	} else if (!strcmp (op->mnemonic, "jnp") ||
                   !strcmp (op->mnemonic, "jpo")) {
		data[l++] = 0x8b;
	} else if (!strcmp (op->mnemonic, "jns")) {
		data[l++] = 0x89;
	} else if (!strcmp (op->mnemonic, "jo")) {
		data[l++] = 0x80;
	} else if (!strcmp (op->mnemonic, "jp") ||
                   !strcmp(op->mnemonic, "jpe")) {
		data[l++] = 0x8a;
	} else if (!strcmp (op->mnemonic, "js") ||
                   !strcmp (op->mnemonic, "jz")) {
		data[l++] = 0x88;
	}
	if (is_short) {
		data[l-1] -= 0x10;
	}

	immediate -= is_short ? 2 : 6;
	data[l++] = immediate;
	if (!is_short) {
		data[l++] = immediate >> 8;
		data[l++] = immediate >> 16;
		data[l++] = immediate >> 24;
	}
	return l;
}