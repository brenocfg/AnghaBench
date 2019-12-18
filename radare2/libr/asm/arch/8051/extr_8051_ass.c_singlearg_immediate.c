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
 int /*<<< orphan*/  resolve_immediate (char const*,int*) ; 

__attribute__((used)) static bool singlearg_immediate(ut8 firstbyte, char const* imm_str, ut8**out) {
	ut16 imm;
	if (imm_str[0] != '#'
		|| !resolve_immediate (imm_str + 1, &imm)) {
		return false;
	}
	(*out)[0] = firstbyte;
	(*out)[1] = imm & 0x00FF;
	*out += 2;
	return true;
}