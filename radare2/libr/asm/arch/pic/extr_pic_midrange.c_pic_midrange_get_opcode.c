#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ut16 ;
typedef  int /*<<< orphan*/  PicMidrangeOpcode ;

/* Variables and functions */
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_ADDFSR ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_ADDLW ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_ADDWF ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_ADDWFC ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_ANDLW ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_ANDWF ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_ASRF ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_BCF ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_BRA ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_BRW ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_BSF ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_BTFSC ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_BTFSS ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_CALL ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_CALLW ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_CLR ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_CLRWDT ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_COMF ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_DECF ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_DECFSZ ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_GOTO ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_INCF ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_INCFSZ ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_INVALID ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_IORLW ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_IORWF ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_LSLF ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_LSRF ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_MOVF ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_MOVIW_1 ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_MOVIW_2 ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_MOVLB ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_MOVLP ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_MOVLW ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_MOVWF ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_MOVWI_1 ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_MOVWI_2 ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_NOP ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_OPTION ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_RESET ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_RETFIE ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_RETLW ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_RETURN ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_RLF ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_RRF ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_SLEEP ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_SUBLW ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_SUBWF ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_SUBWFB ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_SWAPF ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_TRIS ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_XORLW ; 
 int /*<<< orphan*/  PIC_MIDRANGE_OPCODE_XORWF ; 

PicMidrangeOpcode pic_midrange_get_opcode (ut16 instr) {
	if (instr & (1 << 14)) {
		return PIC_MIDRANGE_OPCODE_INVALID;
	}

	switch (instr >> 11) { // 3 first MSB bits
	case 0x4: return PIC_MIDRANGE_OPCODE_CALL;
	case 0x5: return PIC_MIDRANGE_OPCODE_GOTO;
	}

	switch (instr >> 10) { // 4 first MSB bits
	case 0x4: return PIC_MIDRANGE_OPCODE_BCF;
	case 0x5: return PIC_MIDRANGE_OPCODE_BSF;
	case 0x6: return PIC_MIDRANGE_OPCODE_BTFSC;
	case 0x7: return PIC_MIDRANGE_OPCODE_BTFSS;
	}

	switch (instr >> 9) { // 5 first MSB bits
	case 0x19: return PIC_MIDRANGE_OPCODE_BRA;
	}

	switch (instr >> 8) { // 6 first MSB bits
	case 0x1: return PIC_MIDRANGE_OPCODE_CLR;
	case 0x2: return PIC_MIDRANGE_OPCODE_SUBWF;
	case 0x3: return PIC_MIDRANGE_OPCODE_DECF;
	case 0x4: return PIC_MIDRANGE_OPCODE_IORWF;
	case 0x5: return PIC_MIDRANGE_OPCODE_ANDWF;
	case 0x6: return PIC_MIDRANGE_OPCODE_XORWF;
	case 0x7: return PIC_MIDRANGE_OPCODE_ADDWF;
	case 0x8: return PIC_MIDRANGE_OPCODE_MOVF;
	case 0x9: return PIC_MIDRANGE_OPCODE_COMF;
	case 0xa: return PIC_MIDRANGE_OPCODE_INCF;
	case 0xb: return PIC_MIDRANGE_OPCODE_DECFSZ;
	case 0xc: return PIC_MIDRANGE_OPCODE_RRF;
	case 0xd: return PIC_MIDRANGE_OPCODE_RLF;
	case 0xe: return PIC_MIDRANGE_OPCODE_SWAPF;
	case 0xf: return PIC_MIDRANGE_OPCODE_INCFSZ;
	case 0x38: return PIC_MIDRANGE_OPCODE_IORLW;
	case 0x39: return PIC_MIDRANGE_OPCODE_ANDLW;
	case 0x3a: return PIC_MIDRANGE_OPCODE_XORLW;
	case 0x30: return PIC_MIDRANGE_OPCODE_MOVLW;
	case 0x34: return PIC_MIDRANGE_OPCODE_RETLW;
	case 0x3c: return PIC_MIDRANGE_OPCODE_SUBLW;
	case 0x3e: return PIC_MIDRANGE_OPCODE_ADDLW;
	case 0x35: return PIC_MIDRANGE_OPCODE_LSLF;
	case 0x36: return PIC_MIDRANGE_OPCODE_LSRF;
	case 0x37: return PIC_MIDRANGE_OPCODE_ASRF;
	case 0x3b: return PIC_MIDRANGE_OPCODE_SUBWFB;
	case 0x3d: return PIC_MIDRANGE_OPCODE_ADDWFC;
	}

	switch (instr >> 7) { // 7 first MSB bits
	case 0x1: return PIC_MIDRANGE_OPCODE_MOVWF;
	case 0x62: return PIC_MIDRANGE_OPCODE_ADDFSR;
	case 0x63: return PIC_MIDRANGE_OPCODE_MOVLP;
	case 0x7e: return PIC_MIDRANGE_OPCODE_MOVIW_2;
	case 0x7f: return PIC_MIDRANGE_OPCODE_MOVWI_2;
	}

	switch (instr >> 5) { // 9 first MSB bits
	case 0x1: return PIC_MIDRANGE_OPCODE_MOVLB;
	}

	switch (instr >> 3) { // 11 first MSB bits
	case 0x2: return PIC_MIDRANGE_OPCODE_MOVIW_1;
	case 0x3: return PIC_MIDRANGE_OPCODE_MOVWI_1;
	}

	switch (instr >> 2) { // 12 first MSB bits
	case 0x19: return PIC_MIDRANGE_OPCODE_TRIS;
	}

	switch (instr) {
	case 0x0: return PIC_MIDRANGE_OPCODE_NOP;
	case 0x1: return PIC_MIDRANGE_OPCODE_RESET;
	case 0xa: return PIC_MIDRANGE_OPCODE_CALLW;
	case 0xb: return PIC_MIDRANGE_OPCODE_BRW;
	case 0x8: return PIC_MIDRANGE_OPCODE_RETURN;
	case 0x9: return PIC_MIDRANGE_OPCODE_RETFIE;
	case 0x62: return PIC_MIDRANGE_OPCODE_OPTION;
	case 0x63: return PIC_MIDRANGE_OPCODE_SLEEP;
	case 0x64: return PIC_MIDRANGE_OPCODE_CLRWDT;
	}

	return PIC_MIDRANGE_OPCODE_INVALID;
}