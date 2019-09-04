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

/* Variables and functions */
#define  EM_386 139 
#define  EM_AARCH64 138 
#define  EM_ARM 137 
#define  EM_NONE 136 
#define  EM_PPC 135 
#define  EM_PPC64 134 
#define  EM_S390 133 
#define  EM_SH 132 
#define  EM_SPARC 131 
#define  EM_SPARCV9 130 
#define  EM_X86_64 129 
#define  EM_XTENSA 128 
 char const* __get_dwarf_regstr (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  aarch64_regstr_tbl ; 
 int /*<<< orphan*/  arm_regstr_tbl ; 
 char const* get_arch_regstr (unsigned int) ; 
 int /*<<< orphan*/  powerpc_regstr_tbl ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  s390_regstr_tbl ; 
 int /*<<< orphan*/  sh_regstr_tbl ; 
 int /*<<< orphan*/  sparc_regstr_tbl ; 
 int /*<<< orphan*/  x86_32_regstr_tbl ; 
 int /*<<< orphan*/  x86_64_regstr_tbl ; 
 int /*<<< orphan*/  xtensa_regstr_tbl ; 

const char *get_dwarf_regstr(unsigned int n, unsigned int machine)
{
	switch (machine) {
	case EM_NONE:	/* Generic arch - use host arch */
		return get_arch_regstr(n);
	case EM_386:
		return __get_dwarf_regstr(x86_32_regstr_tbl, n);
	case EM_X86_64:
		return __get_dwarf_regstr(x86_64_regstr_tbl, n);
	case EM_ARM:
		return __get_dwarf_regstr(arm_regstr_tbl, n);
	case EM_AARCH64:
		return __get_dwarf_regstr(aarch64_regstr_tbl, n);
	case EM_SH:
		return __get_dwarf_regstr(sh_regstr_tbl, n);
	case EM_S390:
		return __get_dwarf_regstr(s390_regstr_tbl, n);
	case EM_PPC:
	case EM_PPC64:
		return __get_dwarf_regstr(powerpc_regstr_tbl, n);
	case EM_SPARC:
	case EM_SPARCV9:
		return __get_dwarf_regstr(sparc_regstr_tbl, n);
	case EM_XTENSA:
		return __get_dwarf_regstr(xtensa_regstr_tbl, n);
	default:
		pr_err("ELF MACHINE %x is not supported.\n", machine);
	}
	return NULL;
}