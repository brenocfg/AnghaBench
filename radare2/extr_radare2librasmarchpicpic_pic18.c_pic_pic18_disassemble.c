#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ut8 ;
typedef  int ut32 ;
typedef  int ut16 ;
typedef  int /*<<< orphan*/  instr ;
struct TYPE_5__ {int opmin; int opmax; char const* name; int optype; } ;
struct TYPE_4__ {int size; } ;
typedef  TYPE_1__ RAsmOp ;

/* Variables and functions */
#define  AF_T 140 
#define  BAF_T 139 
#define  CALL_T 138 
#define  DAF_T 137 
#define  F32_T 136 
#define  GOTO_T 135 
#define  K_T 134 
#define  LFSR_T 133 
#define  NEX_T 132 
#define  NO_ARG 131 
#define  N_T 130 
#define  SHK_T 129 
#define  S_T 128 
 int* fsr ; 
 int /*<<< orphan*/  memcpy (int*,size_t const*,int) ; 
 TYPE_3__* ops ; 
 char* sdb_fmt (char*,char*,int,...) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

int pic_pic18_disassemble(RAsmOp *op, char *opbuf, const ut8 *b, int blen) {
	int i;
	if (blen < 2) { //well noone loves reading bitstream of size zero or 1 !!
		strcpy (opbuf, "invalid");
		op->size = blen;
		return -1;
	}
	ut16 instr = 0 ; // instruction
	memcpy (&instr, b, sizeof (instr));
	// if still redundan code is reported think of this of instr=0x2
	const char *buf_asm = "invalid";
	strcpy (opbuf, buf_asm);

	for (i = 0; ops[i].opmin != (ops[i].opmin & instr) || ops[i].opmax != (ops[i].opmax | instr); i++) {
		;
	}
	if (ops[i].opmin == 0 && ops[i].opmax == 0xffff) {
		strcpy (opbuf, ops[i].name);
		op->size = 2;
		return -1;
	}
	op->size = 2;
	switch (ops[i].optype) {
	case NO_ARG:
		buf_asm = ops[i].name;
		break;
	case N_T:
	case K_T:
		buf_asm = sdb_fmt ("%s 0x%x", ops[i].name, instr & 0xff);
		break;
	case DAF_T:
		buf_asm = sdb_fmt ("%s 0x%x, %d, %d", ops[i].name, instr & 0xff, (instr >> 9) & 1, (instr >> 8) & 1);
		break;
	case AF_T:
		buf_asm = sdb_fmt ("%s 0x%x, %d", ops[i].name, instr & 0xff, (instr >> 8) & 1);
		break;
	case BAF_T:
		buf_asm = sdb_fmt ("%s 0x%x, %d, %d", ops[i].name, instr & 0xff, (instr >> 9) & 0x7, (instr >> 8) & 0x1);
		break;
	case NEX_T:
		buf_asm = sdb_fmt ("%s 0x%x", ops[i].name, instr & 0x7ff);
		break;
	case CALL_T:
		if (blen < 4) {
			return -1;
		}
		op->size = 4;
		{
		ut32 dword_instr = *(ut32 *)b;
		//I dont even know how the bits are arranged but it works !!!
		//`the wierdness of little endianess`
		if (dword_instr >> 28 != 0xf) {
			return -1;
		}
		buf_asm = sdb_fmt ("%s 0x%x, %d", ops[i].name,
			  (dword_instr & 0xff) | (dword_instr >> 8 & 0xfff00), (dword_instr >> 8) & 0x1);
		}
		break;
	case GOTO_T:
		if (blen < 4) {
			return -1;
		}
		{
		op->size = 4;
		ut32 dword_instr = *(ut32 *)b;
		if (dword_instr >> 28 != 0xf) {
			return -1;
		}
		buf_asm = sdb_fmt ("%s 0x%x", ops[i].name,
			  ((dword_instr & 0xff) | ((dword_instr &  0xfff0000) >>8) )*2);
		}
		break;
	case F32_T:
		if (blen < 4) {
			return -1;
		}
		op->size = 4;
		{
		ut32 dword_instr = *(ut32 *)b;
		if (dword_instr >> 28 != 0xf) {
			return -1;
		}
		buf_asm = sdb_fmt ("%s 0x%x, 0x%x", ops[i].name,
			  dword_instr & 0xfff, (dword_instr >> 16) & 0xfff);
		}
		break;
	case SHK_T:
		buf_asm = sdb_fmt ("%s 0x%x", ops[i].name, instr & 0xf);
		break;
	case S_T:
		buf_asm = sdb_fmt ("%s %d", ops[i].name, instr & 0x1);
		break;
	case LFSR_T: {
		op->size = 4;
		ut32 dword_instr = *(ut32 *)b;
		if (dword_instr >> 28 != 0xf) {
			return -1;
		}
		ut8 reg_n = (dword_instr >> 4) & 0x3;
		buf_asm = sdb_fmt ("%s %s, %d", ops[i].name, fsr[reg_n],
			(dword_instr & 0xf) << 8 | ((dword_instr >> 16) & 0xff));
		break;
	}
	default:
		buf_asm = "unknown args";
	};
	strcpy (opbuf, buf_asm);
	return op->size;
}