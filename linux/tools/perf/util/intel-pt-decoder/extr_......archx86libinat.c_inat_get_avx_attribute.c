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
typedef  scalar_t__ insn_byte_t ;
typedef  int /*<<< orphan*/  const insn_attr_t ;

/* Variables and functions */
 scalar_t__ INAT_LSTPFX_MAX ; 
 scalar_t__ X86_VEX_M_MAX ; 
 int /*<<< orphan*/  const*** inat_avx_tables ; 
 int /*<<< orphan*/  inat_is_group (int /*<<< orphan*/  const) ; 

insn_attr_t inat_get_avx_attribute(insn_byte_t opcode, insn_byte_t vex_m,
				   insn_byte_t vex_p)
{
	const insn_attr_t *table;
	if (vex_m > X86_VEX_M_MAX || vex_p > INAT_LSTPFX_MAX)
		return 0;
	/* At first, this checks the master table */
	table = inat_avx_tables[vex_m][0];
	if (!table)
		return 0;
	if (!inat_is_group(table[opcode]) && vex_p) {
		/* If this is not a group, get attribute directly */
		table = inat_avx_tables[vex_m][vex_p];
		if (!table)
			return 0;
	}
	return table[opcode];
}