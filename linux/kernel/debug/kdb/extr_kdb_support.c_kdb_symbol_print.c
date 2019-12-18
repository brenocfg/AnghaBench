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
struct TYPE_4__ {long sym_name; unsigned long sym_start; unsigned long sym_end; int /*<<< orphan*/  mod_name; } ;
typedef  TYPE_1__ kdb_symtab_t ;

/* Variables and functions */
 unsigned int KDB_SP_NEWLINE ; 
 unsigned int KDB_SP_PAREN ; 
 unsigned int KDB_SP_SPACEA ; 
 unsigned int KDB_SP_SPACEB ; 
 unsigned int KDB_SP_SYMSIZE ; 
 unsigned int KDB_SP_VALUE ; 
 int /*<<< orphan*/  kdb_machreg_fmt0 ; 
 int /*<<< orphan*/  kdb_printf (char*,...) ; 
 int /*<<< orphan*/  kdbnearsym (unsigned long,TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void kdb_symbol_print(unsigned long addr, const kdb_symtab_t *symtab_p,
		      unsigned int punc)
{
	kdb_symtab_t symtab, *symtab_p2;
	if (symtab_p) {
		symtab_p2 = (kdb_symtab_t *)symtab_p;
	} else {
		symtab_p2 = &symtab;
		kdbnearsym(addr, symtab_p2);
	}
	if (!(symtab_p2->sym_name || (punc & KDB_SP_VALUE)))
		return;
	if (punc & KDB_SP_SPACEB)
		kdb_printf(" ");
	if (punc & KDB_SP_VALUE)
		kdb_printf(kdb_machreg_fmt0, addr);
	if (symtab_p2->sym_name) {
		if (punc & KDB_SP_VALUE)
			kdb_printf(" ");
		if (punc & KDB_SP_PAREN)
			kdb_printf("(");
		if (strcmp(symtab_p2->mod_name, "kernel"))
			kdb_printf("[%s]", symtab_p2->mod_name);
		kdb_printf("%s", symtab_p2->sym_name);
		if (addr != symtab_p2->sym_start)
			kdb_printf("+0x%lx", addr - symtab_p2->sym_start);
		if (punc & KDB_SP_SYMSIZE)
			kdb_printf("/0x%lx",
				   symtab_p2->sym_end - symtab_p2->sym_start);
		if (punc & KDB_SP_PAREN)
			kdb_printf(")");
	}
	if (punc & KDB_SP_SPACEA)
		kdb_printf(" ");
	if (punc & KDB_SP_NEWLINE)
		kdb_printf("\n");
}