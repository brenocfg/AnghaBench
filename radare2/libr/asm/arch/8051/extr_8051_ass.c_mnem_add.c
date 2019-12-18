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
 scalar_t__ is_reg (char const* const) ; 
 scalar_t__ r_str_casecmp (char const* const,char*) ; 
 int singlearg_direct (int,char const* const,int /*<<< orphan*/ **) ; 
 int singlearg_immediate (int,char const* const,int /*<<< orphan*/ **) ; 
 int singlearg_register (int,char const* const,int /*<<< orphan*/ **) ; 

__attribute__((used)) static bool mnem_add(char const*const*arg, ut16 pc, ut8**out) {
	if (r_str_casecmp (arg[0], "a")) {
		return false;
	}
	switch (arg[1][0]) {
	break; case '@': case '[':
		return singlearg_register (0x26, arg[1], out);
	break; case '#':
		return singlearg_immediate (0x24, arg[1], out);
	}
	if (is_reg (arg[1])) {
		return singlearg_register (0x28, arg[1], out);
	} else {
		return singlearg_direct (0x25, arg[1], out);
	}
}