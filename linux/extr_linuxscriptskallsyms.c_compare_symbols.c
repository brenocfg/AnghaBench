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
struct sym_entry {scalar_t__ addr; char* sym; int start_pos; } ;

/* Variables and functions */
 int may_be_linker_script_provide_symbol (struct sym_entry const*) ; 
 int prefix_underscores_count (char const*) ; 

__attribute__((used)) static int compare_symbols(const void *a, const void *b)
{
	const struct sym_entry *sa;
	const struct sym_entry *sb;
	int wa, wb;

	sa = a;
	sb = b;

	/* sort by address first */
	if (sa->addr > sb->addr)
		return 1;
	if (sa->addr < sb->addr)
		return -1;

	/* sort by "weakness" type */
	wa = (sa->sym[0] == 'w') || (sa->sym[0] == 'W');
	wb = (sb->sym[0] == 'w') || (sb->sym[0] == 'W');
	if (wa != wb)
		return wa - wb;

	/* sort by "linker script provide" type */
	wa = may_be_linker_script_provide_symbol(sa);
	wb = may_be_linker_script_provide_symbol(sb);
	if (wa != wb)
		return wa - wb;

	/* sort by the number of prefix underscores */
	wa = prefix_underscores_count((const char *)sa->sym + 1);
	wb = prefix_underscores_count((const char *)sb->sym + 1);
	if (wa != wb)
		return wa - wb;

	/* sort by initial order, so that other symbols are left undisturbed */
	return sa->start_pos - sb->start_pos;
}