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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut16 ;

/* Variables and functions */
 scalar_t__ is_indirect_reg (char const* const) ; 
 scalar_t__ r_str_casecmp (char const* const,char*) ; 
 int single_byte_instr (int,int /*<<< orphan*/ **) ; 
 int singlearg_register (int,char const* const,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  str_iwhitecasecmp (char const* const,char*) ; 

__attribute__((used)) static bool mnem_movx(char const*const*arg, ut16 pc, ut8**out) {
	if (!r_str_casecmp (arg[0], "a")) {
		if (is_indirect_reg (arg[1])) {
			return singlearg_register (0xe2, arg[1], out);
		}
		if (!str_iwhitecasecmp (arg[1], "@dptr")
			|| !str_iwhitecasecmp (arg[1], "[dptr]")) {
			return single_byte_instr (0xe0, out);
		}
	}
	if (r_str_casecmp (arg[1], "a")) {
		return false;
	}
	if (is_indirect_reg (arg[0])) {
		return singlearg_register (0xf2, arg[0], out);
	}
	if (!str_iwhitecasecmp (arg[0], "@dptr")
		|| !str_iwhitecasecmp (arg[0], "[dptr]")) {
		return single_byte_instr (0xf0, out);
	}
	return false;
}