#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ printTableFooter ;
struct TYPE_6__ {int ncolumns; int nrows; TYPE_3__* opt; TYPE_1__* footers; } ;
typedef  TYPE_2__ printTableContent ;
struct TYPE_7__ {int /*<<< orphan*/  tuples_only; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * PageOutput (int,TYPE_3__*) ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static void
IsPagerNeeded(const printTableContent *cont, int extra_lines, bool expanded,
			  FILE **fout, bool *is_pager)
{
	if (*fout == stdout)
	{
		int			lines;

		if (expanded)
			lines = (cont->ncolumns + 1) * cont->nrows;
		else
			lines = cont->nrows + 1;

		if (!cont->opt->tuples_only)
		{
			printTableFooter *f;

			/*
			 * FIXME -- this is slightly bogus: it counts the number of
			 * footers, not the number of lines in them.
			 */
			for (f = cont->footers; f; f = f->next)
				lines++;
		}

		*fout = PageOutput(lines + extra_lines, cont->opt);
		*is_pager = (*fout != stdout);
	}
	else
		*is_pager = false;
}