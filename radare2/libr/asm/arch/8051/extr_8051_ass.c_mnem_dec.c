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
 scalar_t__ is_reg (char const* const) ; 
 int /*<<< orphan*/  r_str_casecmp (char*,char const* const) ; 
 int single_byte_instr (int,int /*<<< orphan*/ **) ; 
 int singlearg_direct (int,char const* const,int /*<<< orphan*/ **) ; 
 int singlearg_register (int,char const* const,int /*<<< orphan*/ **) ; 

__attribute__((used)) static bool mnem_dec(char const*const*arg, ut16 pc, ut8**out) {
	if (is_indirect_reg (arg[0])) {
		return singlearg_register (0x16, arg[0], out);
	}
	if (is_reg (arg[0])) {
		return singlearg_register (0x18, arg[0], out);
	}
	if (!r_str_casecmp ("a", arg[0])) {
		return single_byte_instr (0x14, out);
	}
	return singlearg_direct (0x15, arg[0], out);
}