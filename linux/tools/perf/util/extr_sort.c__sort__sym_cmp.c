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
struct symbol {scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  name; scalar_t__ inlined; } ;
typedef  int int64_t ;

/* Variables and functions */
 int cmp_null (struct symbol*,struct symbol*) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t _sort__sym_cmp(struct symbol *sym_l, struct symbol *sym_r)
{
	if (!sym_l || !sym_r)
		return cmp_null(sym_l, sym_r);

	if (sym_l == sym_r)
		return 0;

	if (sym_l->inlined || sym_r->inlined) {
		int ret = strcmp(sym_l->name, sym_r->name);

		if (ret)
			return ret;
		if ((sym_l->start <= sym_r->end) && (sym_l->end >= sym_r->start))
			return 0;
	}

	if (sym_l->start != sym_r->start)
		return (int64_t)(sym_r->start - sym_l->start);

	return (int64_t)(sym_r->end - sym_l->end);
}