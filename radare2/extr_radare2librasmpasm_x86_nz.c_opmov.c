#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int ut64 ;
typedef  int ut32 ;
typedef  int st64 ;
struct TYPE_8__ {int type; int immediate; int sign; int reg; int dest_size; int reg_size; int offset; int offset_sign; int* regs; int* scale; scalar_t__ extended; int /*<<< orphan*/  explicit_size; int /*<<< orphan*/  is_good_flag; } ;
struct TYPE_7__ {TYPE_5__* operands; } ;
struct TYPE_6__ {int bits; } ;
typedef  TYPE_1__ RAsm ;
typedef  TYPE_2__ Opcode ;

/* Variables and functions */
 int ALL_SIZE ; 
 int B0000 ; 
 int B0001 ; 
 int B0010 ; 
 int B0011 ; 
 int B0100 ; 
 int B0101 ; 
 int B0111 ; 
 int OPSIZE_SHIFT ; 
 int OT_BYTE ; 
 int OT_CONSTANT ; 
 int OT_DEBUGREG ; 
 int OT_DWORD ; 
 int OT_GPREG ; 
 int OT_MEMORY ; 
 int OT_QWORD ; 
 int OT_REGALL ; 
 int OT_REGTYPE ; 
 int OT_SEGMENTREG ; 
 int OT_WORD ; 
 int* SEG_REG_PREFIXES ; 
 int UT32_MAX ; 
 int X86R_BP ; 
 int X86R_BX ; 
 int X86R_DI ; 
 int X86R_EAX ; 
 int X86R_EBP ; 
 int X86R_EIP ; 
 int X86R_ESP ; 
 int X86R_R8 ; 
 int X86R_RIP ; 
 int X86R_SI ; 
 int X86R_UNDEFINED ; 
 int getsib (int) ; 
 scalar_t__ is_debug_or_control (TYPE_5__) ; 

__attribute__((used)) static int opmov(RAsm *a, ut8 *data, const Opcode *op) {
	int l = 0;
	st64 offset = 0;
	int mod = 0;
	int base = 0;
	int rex = 0;
	ut64 immediate = 0;
	if (op->operands[1].type & OT_CONSTANT) {
		if (!op->operands[1].is_good_flag) {
			return -1;
		}
		if (op->operands[1].immediate == -1) {
			return -1;
		}
		immediate = op->operands[1].immediate * op->operands[1].sign;
		if (op->operands[0].type & OT_GPREG && !(op->operands[0].type & OT_MEMORY)) {
			if (a->bits == 64 && ((op->operands[0].type & OT_QWORD) | (op->operands[1].type & OT_QWORD))) {
				if (!(op->operands[1].type & OT_CONSTANT) && op->operands[1].extended) {
					data[l++] = 0x49;
				} else {
					data[l++] = 0x48;
				}
			} else if (op->operands[0].extended) {
				data[l++] = 0x41;
			}
			if (op->operands[0].type & OT_WORD) {
				if (a->bits > 16) {
					data[l++] = 0x66;
				}
			}
			if (op->operands[0].type & OT_BYTE) {
				data[l++] = 0xb0 | op->operands[0].reg;
				data[l++] = immediate;
			} else {
				if (a->bits == 64 &&
					((op->operands[0].type & OT_QWORD) |
					(op->operands[1].type & OT_QWORD)) &&
					immediate < UT32_MAX) {
						data[l++] = 0xc7;
				 		data[l++] = 0xc0 | op->operands[0].reg;
				} else {
					data[l++] = 0xb8 | op->operands[0].reg;
				}
				data[l++] = immediate;
				data[l++] = immediate >> 8;
				if (!(op->operands[0].type & OT_WORD)) {
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
		} else if (op->operands[0].type & OT_MEMORY) {
			if (!op->operands[0].explicit_size) {
				if (op->operands[0].type & OT_GPREG) {
					((Opcode *)op)->operands[0].dest_size = op->operands[0].reg_size;
				} else {
					return -1;
				}
			}

			int dest_bits = 8 * ((op->operands[0].dest_size & ALL_SIZE) >> OPSIZE_SHIFT);
			int reg_bits = 8 * ((op->operands[0].reg_size & ALL_SIZE) >> OPSIZE_SHIFT);
			int offset = op->operands[0].offset * op->operands[0].offset_sign;

			//addr_size_override prefix
			bool use_aso = false;
			if (reg_bits < a->bits) {
				use_aso = true;
			}

			//op_size_override prefix
			bool use_oso = false;
			if (dest_bits == 16) {
				use_oso = true;
			}

			bool rip_rel = op->operands[0].regs[0] == X86R_RIP;

			//rex prefix
			int rex = 1 << 6;
			bool use_rex = false;
			if (dest_bits == 64) {			//W field
				use_rex = true;
				rex |= 1 << 3;
			}
			if (op->operands[0].extended) {		//B field
				use_rex = true;
				rex |= 1;
			}

			//opcode selection
			int opcode;
			if (dest_bits == 8) {
				opcode = 0xc6;
			} else {
				opcode = 0xc7;
			}

			//modrm and SIB selection
			int modrm = 0;
			int mod;
			int reg = 0;
			int rm;
			bool use_sib = false;
			int sib;
			//mod
			if (offset == 0) {
				mod = 0;
			} else if (offset < 128 && offset > -129) {
				mod = 1;
			} else {
				mod = 2;
			}

			if (reg_bits == 16) {
				if (op->operands[0].regs[0] == X86R_BX && op->operands[0].regs[1] == X86R_SI) {
					rm = B0000;
				} else if (op->operands[0].regs[0] == X86R_BX && op->operands[0].regs[1] == X86R_DI) {
					rm = B0001;
				} else if (op->operands[0].regs[0] == X86R_BP && op->operands[0].regs[1] == X86R_SI) {
					rm = B0010;
				} else if (op->operands[0].regs[0] == X86R_BP && op->operands[0].regs[1] == X86R_DI) {
					rm = B0011;
				} else if (op->operands[0].regs[0] == X86R_SI && op->operands[0].regs[1] == -1) {
					rm = B0100;
				} else if (op->operands[0].regs[0] == X86R_DI && op->operands[0].regs[1] == -1) {
					rm = B0101;
				} else if (op->operands[0].regs[0] == X86R_BX && op->operands[0].regs[1] == -1) {
					rm = B0111;
				} else {
					//TODO allow for displacement only when parser is reworked
					return -1;
				}
				modrm = (mod << 6) | (reg << 3) | rm;
			} else {
				//rm
				if (op->operands[0].extended) {
					rm = op->operands[0].reg;
				} else {
					rm = op->operands[0].regs[0];
				}
				//[epb] alone is illegal, so we need to fake a [ebp+0]
				if (rm == 5 && mod == 0) {
					mod = 1;
				}

				//sib
				int index = op->operands[0].regs[1];
				int scale = getsib(op->operands[0].scale[1]);
				if (index != -1) {
					use_sib = true;
					sib = (scale << 6) | (index << 3) | rm;
				} else if (rm == 4) {
					use_sib = true;
					sib = 0x24;
				}
				if (use_sib) {
					rm = B0100;
				}
				if (rip_rel) {
					modrm = (B0000 << 6) | (reg << 3) | B0101;
					sib = (scale << 6) | (B0100 << 3) | B0101;
				} else {
					modrm = (mod << 6) | (reg << 3) | rm;
				}
			}

			//build the final result
			if (use_aso) {
				data[l++] = 0x67;
			}
			if (use_oso) {
				data[l++] = 0x66;
			}
			if (use_rex) {
				data[l++] = rex;
			}
			data[l++] = opcode;
			data[l++] = modrm;
			if (use_sib) {
				data[l++] = sib;
			}
			//offset
			if (mod == 1) {
				data[l++] = offset;
			} else if (reg_bits == 16 && mod == 2) {
				data[l++] = offset;
				data[l++] = offset >> 8;
			} else if (mod == 2 || rip_rel) {
				data[l++] = offset;
				data[l++] = offset >> 8;
				data[l++] = offset >> 16;
				data[l++] = offset >> 24;
			}
			//immediate
			int byte;
			for (byte = 0; byte < dest_bits && byte < 32; byte += 8) {
				data[l++] = (immediate >> byte);
			}
		}
	} else if (op->operands[1].type & OT_REGALL &&
			 !(op->operands[1].type & OT_MEMORY)) {
		if (op->operands[0].type & OT_CONSTANT) {
			return -1;
		}
		if (op->operands[0].type & OT_REGTYPE & OT_SEGMENTREG &&
		    op->operands[1].type & OT_REGTYPE & OT_SEGMENTREG) {
				return -1;
		}
		if (is_debug_or_control (op->operands[0]) &&
		   !(op->operands[1].type & OT_REGTYPE & OT_GPREG)) {
			return -1;
		}
		if (is_debug_or_control (op->operands[1]) &&
			!(op->operands[0].type & OT_REGTYPE & OT_GPREG)) {
			return -1;
		}
		// Check reg sizes match
		if (op->operands[0].type & OT_REGTYPE && op->operands[1].type & OT_REGTYPE) {
			if (!((op->operands[0].type & ALL_SIZE) &
			(op->operands[1].type & ALL_SIZE))) {
				return -1;
			}
		}

		if (a->bits == 64) {
			if (op->operands[0].extended) {
				rex = 1;
			}
			if (op->operands[1].extended) {
				rex += 4;
			}
			if (op->operands[1].type & OT_QWORD) {
				if (!(op->operands[0].type & OT_QWORD)) {
					data[l++] = 0x67;
					data[l++] = 0x48;
				}
			}
			if (op->operands[1].type & OT_QWORD &&
				op->operands[0].type & OT_QWORD) {
				data[l++] = 0x48 | rex;
			}
			if (op->operands[1].type & OT_DWORD &&
				op->operands[0].type & OT_DWORD) {
				data[l++] = 0x40 | rex;
			}
		} else if (op->operands[0].extended && op->operands[1].extended) {
			data[l++] = 0x45;
		}
		offset = op->operands[0].offset * op->operands[0].offset_sign;
		if (op->operands[1].type & OT_REGTYPE & OT_SEGMENTREG) {
			data[l++] = 0x8c;
		} else if (is_debug_or_control (op->operands[0])) {
			data[l++] = 0x0f;
			if (op->operands[0].type & OT_REGTYPE & OT_DEBUGREG) {
				data[l++] = 0x23;
			} else {
				data[l++] = 0x22;
			}
		} else if (is_debug_or_control(op->operands[1])) {
			data[l++] = 0x0f;
			if (op->operands[1].type & OT_REGTYPE & OT_DEBUGREG) {
				data[l++] = 0x21;
			} else {
				data[l++] = 0x20;
			}
		} else {
			if (op->operands[0].type & OT_WORD) {
				data[l++] = 0x66;
			}
			data[l++] = (op->operands[0].type & OT_BYTE) ? 0x88 : 0x89;
		}

		if (op->operands[0].scale[0] > 1) {
				data[l++] = op->operands[1].reg << 3 | 4;
				data[l++] = getsib (op->operands[0].scale[0]) << 6 |
						    op->operands[0].regs[0] << 3 | 5;

				data[l++] = offset;
				data[l++] = offset >> 8;
				data[l++] = offset >> 16;
				data[l++] = offset >> 24;

				return l;
			}

		if (!(op->operands[0].type & OT_MEMORY)) {
			if (op->operands[0].reg == X86R_UNDEFINED ||
				op->operands[1].reg == X86R_UNDEFINED) {
				return -1;
			}
			mod = 0x3;
			data[l++] = (is_debug_or_control (op->operands[0]))
				? mod << 6 | op->operands[0].reg << 3 | op->operands[1].reg
				: mod << 6 | op->operands[1].reg << 3 | op->operands[0].reg;
		} else if (op->operands[0].regs[0] == X86R_UNDEFINED) {
			data[l++] = op->operands[1].reg << 3 | 0x5;
			data[l++] = offset;
			data[l++] = offset >> 8;
			data[l++] = offset >> 16;
			data[l++] = offset >> 24;
		} else {
			if (op->operands[0].type & OT_MEMORY) {
				if (op->operands[0].regs[1] != X86R_UNDEFINED) {
					data[l++] = op->operands[1].reg << 3 | 0x4;
					data[l++] = op->operands[0].regs[1] << 3 | op->operands[0].regs[0];
					return l;
				}
				if (offset) {
					mod = (offset > 128 || offset < -129) ? 0x2 : 0x1;
				}
				if (op->operands[0].regs[0] == X86R_EBP) {
					mod = 0x2;
				}
				data[l++] = mod << 6 | op->operands[1].reg << 3 | op->operands[0].regs[0];
				if (op->operands[0].regs[0] == X86R_ESP) {
					data[l++] = 0x24;
				}
				if (offset) {
					data[l++] = offset;
				}
				if (mod == 2) {
					// warning C4293: '>>': shift count negative or too big, undefined behavior
					data[l++] = offset >> 8;
					data[l++] = offset >> 16;
					data[l++] = offset >> 24;
				}
			}
		}
	} else if (op->operands[1].type & OT_MEMORY) {
		if (op->operands[0].type & OT_MEMORY) {
			return -1;
		}
		offset = op->operands[1].offset * op->operands[1].offset_sign;
		if (op->operands[0].reg == X86R_EAX && op->operands[1].regs[0] == X86R_UNDEFINED) {
			if (a->bits == 64) {
				data[l++] = 0x48;
			}
			if (op->operands[0].type & OT_BYTE) {
				data[l++] = 0xa0;
			} else {
				data[l++] = 0xa1;
			}
			data[l++] = offset;
			data[l++] = offset >> 8;
			data[l++] = offset >> 16;
			data[l++] = offset >> 24;
			if (a->bits == 64) {
				data[l++] = offset >> 32;
				data[l++] = offset >> 40;
				data[l++] = offset >> 48;
				data[l++] = offset >> 54;
			}
			return l;
		}
		if (op->operands[0].type & OT_BYTE && a->bits == 64 && op->operands[1].regs[0]) {
			if (op->operands[1].regs[0] >= X86R_R8 &&
			    op->operands[0].reg < 4) {
				data[l++] = 0x41;
				data[l++] = 0x8a;
				data[l++] = op->operands[0].reg << 3 | (op->operands[1].regs[0] - 8);
				return l;
			}
			return -1;
		}

		if (op->operands[1].type & OT_REGTYPE & OT_SEGMENTREG) {
			if (op->operands[1].scale[0] == 0) {
				return -1;
			}
			data[l++] = SEG_REG_PREFIXES[op->operands[1].regs[0] % 6];
			data[l++] = 0x8b;
			data[l++] = (((ut32)op->operands[0].reg) << 3) | 0x5;
			data[l++] = offset;
			data[l++] = offset >> 8;
			data[l++] = offset >> 16;
			data[l++] = offset >> 24;
			return l;
		}

		if (a->bits == 64) {
			if (op->operands[0].type & OT_QWORD) {
				if (!(op->operands[1].type & OT_QWORD)) {
					if (op->operands[1].regs[0] != -1) {
						data[l++] = 0x67;
					}
					data[l++] = 0x48;
				}
			} else if (op->operands[1].type & OT_DWORD) {
				data[l++] = 0x44;
			} else if (!(op->operands[1].type & OT_QWORD)) {
				data[l++] = 0x67;
			}
			if (op->operands[1].type & OT_QWORD &&
				op->operands[0].type & OT_QWORD) {
				data[l++] = 0x48;
			}
		}

		if (op->operands[0].type & OT_WORD) {
			data[l++] = 0x66;
			data[l++] = op->operands[1].type & OT_BYTE ? 0x8a : 0x8b;
		} else {
			data[l++] = (op->operands[1].type & OT_BYTE ||
				op->operands[0].type & OT_BYTE) ?
				0x8a : 0x8b;
		}

		if (op->operands[1].regs[0] == X86R_UNDEFINED) {
			if (a->bits == 64) {
				data[l++] = op->operands[0].reg << 3 | 0x4;
				data[l++] = 0x25;
			} else {
				data[l++] = op->operands[0].reg << 3 | 0x5;
			}
			data[l++] = offset;
			data[l++] = offset >> 8;
			data[l++] = offset >> 16;
			data[l++] = offset >> 24;
		} else {
			if (op->operands[1].scale[0] > 1) {
				data[l++] = op->operands[0].reg << 3 | 4;

				if (op->operands[1].scale[0] >= 2) {
					base = 5;
				}
				if (base) {
					data[l++] = getsib (op->operands[1].scale[0]) << 6 | op->operands[1].regs[0] << 3 | base;
				} else {
					data[l++] = getsib (op->operands[1].scale[0]) << 3 | op->operands[1].regs[0];
				}
				if (offset || base) {
					data[l++] = offset;
					data[l++] = offset >> 8;
					data[l++] = offset >> 16;
					data[l++] = offset >> 24;
				}
				return l;
			}
			if (op->operands[1].regs[1] != X86R_UNDEFINED) {
				data[l++] = op->operands[0].reg << 3 | 0x4;
				data[l++] = op->operands[1].regs[1] << 3 | op->operands[1].regs[0];
				return l;
			}

			if (offset || op->operands[1].regs[0] == X86R_EBP) {
				mod = 0x2;
				if (op->operands[1].offset > 127) {
					mod = 0x4;
				}
			}
			if (a->bits == 64 && offset && op->operands[0].type & OT_QWORD) {
				if (op->operands[1].regs[0] == X86R_RIP) {
					data[l++] = 0x5;
				} else {
					if (op->operands[1].offset > 127) {
						data[l++] = 0x80 | op->operands[0].reg << 3 | op->operands[1].regs[0];
					} else {
						data[l++] = 0x40 | op->operands[1].regs[0];
					}
				}
				if (op->operands[1].offset > 127) {
					mod = 0x1;
				}
			} else {
				if (op->operands[1].regs[0] == X86R_EIP && (op->operands[0].type & OT_DWORD)) {
					data[l++] = 0x0d;
				} else if (op->operands[1].regs[0] == X86R_RIP && (op->operands[0].type & OT_QWORD)) {
					data[l++] = 0x05;
				} else {
					data[l++] = mod << 5 | op->operands[0].reg << 3 | op->operands[1].regs[0];
				}
			}
			if (op->operands[1].regs[0] == X86R_ESP) {
				data[l++] = 0x24;
			}
			if (mod >= 0x2) {
				data[l++] = offset;
				if (op->operands[1].offset > 128 || op->operands[1].regs[0] == X86R_EIP) {
					data[l++] = offset >> 8;
					data[l++] = offset >> 16;
					data[l++] = offset >> 24;
				}
			} else if (a->bits == 64 && (offset || op->operands[1].regs[0] == X86R_RIP)) {
				data[l++] = offset;
				if (op->operands[1].offset > 127 || op->operands[1].regs[0] == X86R_RIP) {
					data[l++] = offset >> 8;
					data[l++] = offset >> 16;
					data[l++] = offset >> 24;
				}
			}
		}
	}
	return l;
}