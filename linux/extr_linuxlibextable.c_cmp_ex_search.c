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
struct exception_table_entry {int dummy; } ;

/* Variables and functions */
 unsigned long ex_to_insn (struct exception_table_entry const*) ; 

__attribute__((used)) static int cmp_ex_search(const void *key, const void *elt)
{
	const struct exception_table_entry *_elt = elt;
	unsigned long _key = *(unsigned long *)key;

	/* avoid overflow */
	if (_key > ex_to_insn(_elt))
		return 1;
	if (_key < ex_to_insn(_elt))
		return -1;
	return 0;
}