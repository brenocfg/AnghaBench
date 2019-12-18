#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int ut64 ;
typedef  int ut16 ;
typedef  int st64 ;
struct TYPE_6__ {int addend; int rva; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  io; int /*<<< orphan*/  (* write_at ) (int /*<<< orphan*/ ,int,int*,int) ;int /*<<< orphan*/  (* read_at ) (int /*<<< orphan*/ ,int,int*,int) ;} ;
typedef  TYPE_1__ RIOBind ;
typedef  TYPE_2__ RBinElfReloc ;

/* Variables and functions */
#define  EM_PPC64 147 
#define  EM_X86_64 146 
#define  R_PPC64_REL14 145 
#define  R_PPC64_REL16_HA 144 
#define  R_PPC64_REL16_LO 143 
#define  R_PPC64_REL24 142 
#define  R_PPC64_REL32 141 
#define  R_X86_64_16 140 
#define  R_X86_64_32 139 
#define  R_X86_64_32S 138 
#define  R_X86_64_64 137 
#define  R_X86_64_8 136 
#define  R_X86_64_GLOB_DAT 135 
#define  R_X86_64_JUMP_SLOT 134 
#define  R_X86_64_PC16 133 
#define  R_X86_64_PC32 132 
#define  R_X86_64_PC64 131 
#define  R_X86_64_PC8 130 
#define  R_X86_64_PLT32 129 
#define  R_X86_64_RELATIVE 128 
 int r_read_le32 (int*) ; 
 int /*<<< orphan*/  r_write_le16 (int*,int) ; 
 int /*<<< orphan*/  r_write_le32 (int*,int) ; 
 int /*<<< orphan*/  r_write_le64 (int*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static void _patch_reloc(ut16 e_machine, RIOBind *iob, RBinElfReloc *rel, ut64 S, ut64 B, ut64 L) {
	ut64 val;
	ut64 A = rel->addend, P = rel->rva;
	ut8 buf[8];
	switch (e_machine) {
	case EM_PPC64: {
		int low = 0, word = 0;
		switch (rel->type) {
		case R_PPC64_REL16_HA:
			word = 2;
			val = (S + A - P + 0x8000) >> 16;
			break;
		case R_PPC64_REL16_LO:
			word = 2;
			val = (S + A - P) & 0xffff;
			break;
		case R_PPC64_REL14:
			low = 14;
			val = (st64)(S + A - P) >> 2;
			break;
		case R_PPC64_REL24:
			low = 24;
			val = (st64)(S + A - P) >> 2;
			break;
		case R_PPC64_REL32:
			word = 4;
			val = S + A - P;
			break;
		default:
			break;
		}
		if (low) {
			// TODO big-endian
			switch (low) {
			case 14:
				val &= (1 << 14) - 1;
				iob->read_at (iob->io, rel->rva, buf, 2);
				r_write_le32 (buf, (r_read_le32 (buf) & ~((1<<16) - (1<<2))) | val << 2);
				iob->write_at (iob->io, rel->rva, buf, 2);
				break;
			case 24:
				val &= (1 << 24) - 1;
				iob->read_at (iob->io, rel->rva, buf, 4);
				r_write_le32 (buf, (r_read_le32 (buf) & ~((1<<26) - (1<<2))) | val << 2);
				iob->write_at (iob->io, rel->rva, buf, 4);
				break;
			}
		} else if (word) {
			// TODO big-endian
			switch (word) {
			case 2:
				r_write_le16 (buf, val);
				iob->write_at (iob->io, rel->rva, buf, 2);
				break;
			case 4:
				r_write_le32 (buf, val);
				iob->write_at (iob->io, rel->rva, buf, 4);
				break;
			}
		}
		break;
	}
	case EM_X86_64: {
		int word = 0;
		switch (rel->type) {
		case R_X86_64_8:
			word = 1;
			val = S + A;
			break;
		case R_X86_64_16:
			word = 2;
			val = S + A;
			break;
		case R_X86_64_32:
		case R_X86_64_32S:
			word = 4;
			val = S + A;
			break;
		case R_X86_64_64:
			word = 8;
			val = S + A;
			break;
		case R_X86_64_GLOB_DAT:
		case R_X86_64_JUMP_SLOT:
			word = 4;
			val = S;
			break;
		case R_X86_64_PC8:
			word = 1;
			val = S + A - P;
			break;
		case R_X86_64_PC16:
			word = 2;
			val = S + A - P;
			break;
		case R_X86_64_PC32:
			word = 4;
			val = S + A - P;
			break;
		case R_X86_64_PC64:
			word = 8;
			val = S + A - P;
			break;
		case R_X86_64_PLT32:
			word = 4;
			val = L + A - P;
			break;
		case R_X86_64_RELATIVE:
			word = 8;
			val = B + A;
			break;
		default:
			//eprintf ("relocation %d not handle at this time\n", rel->type);
			break;
		}
		switch (word) {
		case 0:
			break;
		case 1:
			buf[0] = val;
			iob->write_at (iob->io, rel->rva, buf, 1);
			break;
		case 2:
			r_write_le16 (buf, val);
			iob->write_at (iob->io, rel->rva, buf, 2);
			break;
		case 4:
			r_write_le32 (buf, val);
			iob->write_at (iob->io, rel->rva, buf, 4);
			break;
		case 8:
			r_write_le64 (buf, val);
			iob->write_at (iob->io, rel->rva, buf, 8);
			break;
		}
		break;
	}
	}
}