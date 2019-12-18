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
 int /*<<< orphan*/  to_address (char const* const,int*) ; 

__attribute__((used)) static bool mnem_lcall(char const*const*arg, ut16 pc, ut8**out) {
	ut16 address;
	if (!to_address (arg[0], &address)) {
		return false;
	}
	(*out)[0] = 0x12;
	(*out)[1] = ((address & 0xFF00) >> 8) & 0x00FF;
	(*out)[2] = address & 0x00FF;
	*out += 3;
	return true;
}