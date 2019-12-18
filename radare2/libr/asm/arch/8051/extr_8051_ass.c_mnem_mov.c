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
typedef  int ut16 ;

/* Variables and functions */
 int /*<<< orphan*/  address_direct (char const* const,int*) ; 
 scalar_t__ is_indirect_reg (char const* const) ; 
 scalar_t__ is_reg (char const* const) ; 
 int /*<<< orphan*/  r_str_casecmp (char const* const,char*) ; 
 int register_number (char const* const) ; 
 int /*<<< orphan*/  resolve_immediate (char const* const,int*) ; 
 int singlearg_bit (int,char const* const,int**) ; 
 int singlearg_direct (int,char const* const,int**) ; 
 int singlearg_immediate (int,char const* const,int**) ; 
 int singlearg_register (int,char const* const,int**) ; 

__attribute__((used)) static bool mnem_mov(char const*const*arg, ut16 pc, ut8**out) {
	if (!r_str_casecmp (arg[0], "dptr")) {
		ut16 imm;
		if (!resolve_immediate (arg[1] + 1, &imm)) {
			return false;
		}
		(*out)[0] = 0x90;
		(*out)[1] = imm >> 8;
		(*out)[2] = imm;
		*out += 3;
		return true;
	}
	if (is_indirect_reg (arg[0])) {
		if (!r_str_casecmp (arg[1], "a")) {
			return singlearg_register (0xf6, arg[0], out);
		}
		if (arg[1][0] != '#' ) {
			return singlearg_direct (
				0xa6 | register_number (arg[0])
				, arg[1]
				, out);
		}
		return singlearg_immediate (0x76 | register_number (arg[0])
			, arg[1]
			, out);
	}
	if (!r_str_casecmp (arg[0], "a")) {
		if (is_indirect_reg (arg[1])) {
			return singlearg_register (0xe6, arg[1], out);
		}
		if (is_reg (arg[1])) {
			return singlearg_register (0xe8, arg[1], out);
		}
		if (arg[1][0] == '#') {
			return singlearg_immediate (0x74, arg[1], out);
		}
		return singlearg_direct (0xe5, arg[1], out);
	}
	if (is_reg (arg[0])) {
		if (!r_str_casecmp (arg[1], "a")) {
			return singlearg_register (0xf8, arg[0], out);
		}
		if (arg[1][0] == '#') {
			return singlearg_immediate (
				0x78 | register_number (arg[0])
				, arg[1]
				, out);
		}
		return singlearg_direct (0xa8 | register_number (arg[0])
			, arg[1]
			, out);
	}
	if (!r_str_casecmp (arg[1], "c")) {
		return singlearg_bit (0x92, arg[0], out);
	}
	if (!r_str_casecmp (arg[1], "a")) {
		return singlearg_direct (0xf5,  arg[0], out);
	}
	if (is_reg (arg[1])) {
		return singlearg_direct (0x88 | register_number (arg[1])
			, arg[0]
			, out);
	}
	if (is_indirect_reg (arg[1])) {
		return singlearg_direct (0x86 | register_number (arg[1])
			, arg[0]
			, out);
	}
	ut8 dest_addr;
	if (!address_direct (arg[0], &dest_addr)) {
		return false;
	}
	if (arg[1][0] == '#') {
		ut16 imm;
		if (!resolve_immediate (arg[1] + 1, &imm)) {
			return false;
		}
		(*out)[0] = 0x75;
		(*out)[1] = dest_addr;
		(*out)[2] = imm & 0x00FF;
		*out += 3;
		return true;
	}
	ut8 src_addr;
	if (!address_direct (arg[1], &src_addr)) {
		return false;
	}
	(*out)[0] = 0x85;
	(*out)[1] = src_addr;
	(*out)[2] = dest_addr;
	*out += 3;
	return true;
}