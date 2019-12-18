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
typedef  int /*<<< orphan*/  kdb_symtab_t ;

/* Variables and functions */
 int KDB_SP_NEWLINE ; 
 int KDB_SP_SYMSIZE ; 
 int KDB_SP_VALUE ; 
 int /*<<< orphan*/  kdb_printf (char*,...) ; 
 int /*<<< orphan*/  kdb_symbol_print (unsigned long,int /*<<< orphan*/ *,int) ; 
 scalar_t__ kdbnearsym (unsigned long,int /*<<< orphan*/ *) ; 

void kdb_print_nameval(const char *name, unsigned long val)
{
	kdb_symtab_t symtab;
	kdb_printf("  %-11.11s ", name);
	if (kdbnearsym(val, &symtab))
		kdb_symbol_print(val, &symtab,
				 KDB_SP_VALUE|KDB_SP_SYMSIZE|KDB_SP_NEWLINE);
	else
		kdb_printf("0x%lx\n", val);
}