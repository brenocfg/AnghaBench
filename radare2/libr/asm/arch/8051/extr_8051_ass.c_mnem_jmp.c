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
typedef  scalar_t__ ut16 ;

/* Variables and functions */
 int mnem_ajmp (char const* const*,scalar_t__,int /*<<< orphan*/ **) ; 
 int mnem_ljmp (char const* const*,scalar_t__,int /*<<< orphan*/ **) ; 
 int mnem_sjmp (char const* const*,scalar_t__,int /*<<< orphan*/ **) ; 
 int single_byte_instr (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  str_iwhitecasecmp (char const* const,char*) ; 
 int /*<<< orphan*/  to_address (char const* const,scalar_t__*) ; 

__attribute__((used)) static bool mnem_jmp(char const*const*arg, ut16 pc, ut8**out) {
	if (!str_iwhitecasecmp (arg[0], "@a+dptr")
		|| !str_iwhitecasecmp (arg[0], "[a+dptr]")) {
		return single_byte_instr (0x73, out);
	}

	ut16 address;
	if (!to_address (arg[0], &address)) {
		return false;
	}
	ut16 reladdr;
	if ( pc < address ) {
		reladdr = address - pc;
	}
	else {
		reladdr = pc - address;
	}

	if ( reladdr < 0x100 ) {
		return mnem_sjmp (arg, pc, out);
	}
	else if ( reladdr < 0x08FF ) {
		return mnem_ajmp (arg, pc, out);
	}
	else {
		return mnem_ljmp (arg, pc, out);
	}
}