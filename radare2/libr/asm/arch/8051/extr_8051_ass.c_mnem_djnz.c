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
typedef  int /*<<< orphan*/  ut16 ;

/* Variables and functions */
 int /*<<< orphan*/  address_direct (char const* const,int*) ; 
 scalar_t__ is_reg (char const* const) ; 
 int register_number (char const* const) ; 
 int /*<<< orphan*/  relative_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  to_address (char const* const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool mnem_djnz(char const*const*arg, ut16 pc, ut8**out) {
	ut16 jmp_address;
	if (!to_address (arg[1], &jmp_address)) {
		return false;
	}
	if (!relative_address (pc, jmp_address, (*out) + 2)) {
		return false;
	}

	if (is_reg (arg[0])) {
		(*out)[0] = 0xd8 | register_number (arg[0]);
		(*out)[1] = (*out)[2];
		*out += 2;
		return true;
	}
	ut8 dec_address;
	if (!address_direct (arg[0], &dec_address))  {
		return false;
	}
	(*out)[0] = 0xd5;
	(*out)[1] = dec_address;
	(*out)[2] -= 1;
	*out += 3;
	return true;
}