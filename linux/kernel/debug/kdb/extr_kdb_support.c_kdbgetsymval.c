#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sym_start; } ;
typedef  TYPE_1__ kdb_symtab_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR ; 
 scalar_t__ KDB_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kallsyms_lookup_name (char const*) ; 
 int /*<<< orphan*/  kdb_printf (char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int kdbgetsymval(const char *symname, kdb_symtab_t *symtab)
{
	if (KDB_DEBUG(AR))
		kdb_printf("kdbgetsymval: symname=%s, symtab=%px\n", symname,
			   symtab);
	memset(symtab, 0, sizeof(*symtab));
	symtab->sym_start = kallsyms_lookup_name(symname);
	if (symtab->sym_start) {
		if (KDB_DEBUG(AR))
			kdb_printf("kdbgetsymval: returns 1, "
				   "symtab->sym_start=0x%lx\n",
				   symtab->sym_start);
		return 1;
	}
	if (KDB_DEBUG(AR))
		kdb_printf("kdbgetsymval: returns 0\n");
	return 0;
}