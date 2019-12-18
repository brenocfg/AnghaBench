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
 int /*<<< orphan*/  parse_hexadecimal (char const*,int*) ; 

__attribute__((used)) static bool address_direct(char const* addr_str, ut8* addr_out) {
	ut16 addr_big;
	// rasm2 resolves symbols, so does this really only need to parse hex?
	// maybe TODO: check address bounds?
	if ( !parse_hexadecimal (addr_str, &addr_big)
		|| (0xFF < addr_big)) {
		return false;
	}
	*addr_out = addr_big;
	return true;
}