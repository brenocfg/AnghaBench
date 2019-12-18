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
typedef  int ut8 ;
typedef  int /*<<< orphan*/  amd29k_instr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMD29K_SET_VALUE (int /*<<< orphan*/ *,int,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMD29K_TYPE_IMM ; 
 int /*<<< orphan*/  AMD29K_TYPE_REG ; 

__attribute__((used)) static void decode_convert(amd29k_instr_t* instruction, const ut8* buffer) {
	// lambda w,ea: (w >> 24,[decode_byte1(w), decode_byte2(w), ('imm',False,(w&0x80)>>7), ('imm',False,(w&0x70)>>4), ('imm',False,(w&0xC)>>2), ('imm',False, w&3)])
	AMD29K_SET_VALUE (instruction, 0, buffer[1], AMD29K_TYPE_REG);
	AMD29K_SET_VALUE (instruction, 1, buffer[2], AMD29K_TYPE_REG);
	AMD29K_SET_VALUE (instruction, 2, ((buffer[3] & 0x80) >> 7), AMD29K_TYPE_IMM);
	AMD29K_SET_VALUE (instruction, 3, ((buffer[3] & 0x70) >> 4), AMD29K_TYPE_IMM);
	AMD29K_SET_VALUE (instruction, 4, ((buffer[3] & 0x0c) >> 2), AMD29K_TYPE_IMM);
	AMD29K_SET_VALUE (instruction, 5, (buffer[3] & 0x03), AMD29K_TYPE_IMM);
}