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
typedef  size_t u16 ;

/* Variables and functions */
 size_t ARRAY_SIZE (int const*) ; 
#define  BPF_A 165 
#define  BPF_ABS 164 
#define  BPF_ADD 163 
#define  BPF_ALU 162 
#define  BPF_AND 161 
#define  BPF_B 160 
#define  BPF_DIV 159 
#define  BPF_H 158 
#define  BPF_IMM 157 
#define  BPF_IND 156 
#define  BPF_JA 155 
#define  BPF_JEQ 154 
#define  BPF_JGE 153 
#define  BPF_JGT 152 
#define  BPF_JMP 151 
#define  BPF_JSET 150 
#define  BPF_K 149 
#define  BPF_LD 148 
#define  BPF_LDX 147 
#define  BPF_LEN 146 
#define  BPF_LSH 145 
#define  BPF_MEM 144 
#define  BPF_MISC 143 
#define  BPF_MOD 142 
#define  BPF_MSH 141 
#define  BPF_MUL 140 
#define  BPF_NEG 139 
#define  BPF_OR 138 
#define  BPF_RET 137 
#define  BPF_RSH 136 
#define  BPF_ST 135 
#define  BPF_STX 134 
#define  BPF_SUB 133 
#define  BPF_TAX 132 
#define  BPF_TXA 131 
#define  BPF_W 130 
#define  BPF_X 129 
#define  BPF_XOR 128 

__attribute__((used)) static bool chk_code_allowed(u16 code_to_probe)
{
	static const bool codes[] = {
		/* 32 bit ALU operations */
		[BPF_ALU | BPF_ADD | BPF_K] = true,
		[BPF_ALU | BPF_ADD | BPF_X] = true,
		[BPF_ALU | BPF_SUB | BPF_K] = true,
		[BPF_ALU | BPF_SUB | BPF_X] = true,
		[BPF_ALU | BPF_MUL | BPF_K] = true,
		[BPF_ALU | BPF_MUL | BPF_X] = true,
		[BPF_ALU | BPF_DIV | BPF_K] = true,
		[BPF_ALU | BPF_DIV | BPF_X] = true,
		[BPF_ALU | BPF_MOD | BPF_K] = true,
		[BPF_ALU | BPF_MOD | BPF_X] = true,
		[BPF_ALU | BPF_AND | BPF_K] = true,
		[BPF_ALU | BPF_AND | BPF_X] = true,
		[BPF_ALU | BPF_OR | BPF_K] = true,
		[BPF_ALU | BPF_OR | BPF_X] = true,
		[BPF_ALU | BPF_XOR | BPF_K] = true,
		[BPF_ALU | BPF_XOR | BPF_X] = true,
		[BPF_ALU | BPF_LSH | BPF_K] = true,
		[BPF_ALU | BPF_LSH | BPF_X] = true,
		[BPF_ALU | BPF_RSH | BPF_K] = true,
		[BPF_ALU | BPF_RSH | BPF_X] = true,
		[BPF_ALU | BPF_NEG] = true,
		/* Load instructions */
		[BPF_LD | BPF_W | BPF_ABS] = true,
		[BPF_LD | BPF_H | BPF_ABS] = true,
		[BPF_LD | BPF_B | BPF_ABS] = true,
		[BPF_LD | BPF_W | BPF_LEN] = true,
		[BPF_LD | BPF_W | BPF_IND] = true,
		[BPF_LD | BPF_H | BPF_IND] = true,
		[BPF_LD | BPF_B | BPF_IND] = true,
		[BPF_LD | BPF_IMM] = true,
		[BPF_LD | BPF_MEM] = true,
		[BPF_LDX | BPF_W | BPF_LEN] = true,
		[BPF_LDX | BPF_B | BPF_MSH] = true,
		[BPF_LDX | BPF_IMM] = true,
		[BPF_LDX | BPF_MEM] = true,
		/* Store instructions */
		[BPF_ST] = true,
		[BPF_STX] = true,
		/* Misc instructions */
		[BPF_MISC | BPF_TAX] = true,
		[BPF_MISC | BPF_TXA] = true,
		/* Return instructions */
		[BPF_RET | BPF_K] = true,
		[BPF_RET | BPF_A] = true,
		/* Jump instructions */
		[BPF_JMP | BPF_JA] = true,
		[BPF_JMP | BPF_JEQ | BPF_K] = true,
		[BPF_JMP | BPF_JEQ | BPF_X] = true,
		[BPF_JMP | BPF_JGE | BPF_K] = true,
		[BPF_JMP | BPF_JGE | BPF_X] = true,
		[BPF_JMP | BPF_JGT | BPF_K] = true,
		[BPF_JMP | BPF_JGT | BPF_X] = true,
		[BPF_JMP | BPF_JSET | BPF_K] = true,
		[BPF_JMP | BPF_JSET | BPF_X] = true,
	};

	if (code_to_probe >= ARRAY_SIZE(codes))
		return false;

	return codes[code_to_probe];
}