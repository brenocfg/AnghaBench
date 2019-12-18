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
 scalar_t__ AMD29K_HAS_BIT (int const*) ; 
 int /*<<< orphan*/  AMD29K_SET_INVALID (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  AMD29K_SET_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMD29K_TYPE_IMM ; 
 int /*<<< orphan*/  AMD29K_TYPE_JMP ; 

__attribute__((used)) static void decode_imm16_sh2(amd29k_instr_t* instruction, const ut8* buffer) {
	int word = (buffer[1] << 10) + (buffer[3] << 2);
	if (word & 0x20000) {
		word = (int)(0xfffc0000 | word);
	}
	AMD29K_SET_VALUE (instruction, 0, word, AMD29K_HAS_BIT (buffer) ? AMD29K_TYPE_JMP : AMD29K_TYPE_IMM);
	AMD29K_SET_INVALID (instruction, 1);
	AMD29K_SET_INVALID (instruction, 2);
	AMD29K_SET_INVALID (instruction, 3);
	AMD29K_SET_INVALID (instruction, 4);
	AMD29K_SET_INVALID (instruction, 5);
}