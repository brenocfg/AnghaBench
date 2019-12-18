#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sym_match {scalar_t__ eo; scalar_t__ so; TYPE_1__* sym; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sym_rel_comp(const void *sym1, const void *sym2)
{
	const struct sym_match *s1 = sym1;
	const struct sym_match *s2 = sym2;
	int exact1, exact2;

	/* Exact match:
	 * - if matched length on symbol s1 is the length of that symbol,
	 *   then this symbol should come first;
	 * - if matched length on symbol s2 is the length of that symbol,
	 *   then this symbol should come first.
	 * Note: since the search can be a regexp, both symbols may match
	 * exactly; if this is the case, we can't decide which comes first,
	 * and we fallback to sorting alphabetically.
	 */
	exact1 = (s1->eo - s1->so) == strlen(s1->sym->name);
	exact2 = (s2->eo - s2->so) == strlen(s2->sym->name);
	if (exact1 && !exact2)
		return -1;
	if (!exact1 && exact2)
		return 1;

	/* As a fallback, sort symbols alphabetically */
	return strcmp(s1->sym->name, s2->sym->name);
}