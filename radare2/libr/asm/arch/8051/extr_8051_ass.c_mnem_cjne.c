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
 int /*<<< orphan*/  relative_address (int,int,int*) ; 
 int /*<<< orphan*/  resolve_immediate (char const* const,int*) ; 
 int /*<<< orphan*/  to_address (char const* const,int*) ; 

__attribute__((used)) static bool mnem_cjne(char const*const*arg, ut16 pc, ut8**out) {
	ut16 address;
	if (!to_address (arg[2], &address)
		|| !relative_address (pc+1, address, (*out)+2)) {
		return false;
	}
	if (!r_str_casecmp (arg[0], "a")) {
		if (arg[1][0] == '#') {
			ut16 imm;
			if (!resolve_immediate (arg[1] + 1, &imm)) {
				return false;
			}
			(*out)[0] = 0xb4;
			(*out)[1] = imm & 0x00FF;
			// out[2] set earlier
			*out += 3;
			return true;
		}
		ut8 address;
		if (!address_direct (arg[1], &address)) {
			return false;
		}
		(*out)[0] = 0xb5;
		(*out)[1] = address;
		// out[2] set earlier
		*out += 3;
		return true;
	}
	if (is_reg (arg[0])) {
		ut16 imm;
		if (!resolve_immediate (arg[1] + 1, &imm)) {
			return false;
		}
		(*out)[0] = 0xbf | register_number (arg[0]) ;
		(*out)[1] = imm & 0x00FF;
		// out[2] set earlier
		*out += 3;
		return true;
	}
	if (is_indirect_reg (arg[0])) {
		ut16 imm;
		if (!resolve_immediate (arg[1] + 1, &imm)) {
			return false;
		}
		(*out)[0] = 0xb6 | register_number (arg[0]) ;
		(*out)[1] = imm & 0x00FF;
		// out[2] set earlier
		*out += 3;
		return true;
	}
	return false;
}