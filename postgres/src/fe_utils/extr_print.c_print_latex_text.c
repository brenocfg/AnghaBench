#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char const* const data; struct TYPE_8__* next; } ;
typedef  TYPE_2__ printTableFooter ;
struct TYPE_9__ {char const* const title; unsigned int ncolumns; char* aligns; char** headers; char** cells; TYPE_1__* opt; } ;
typedef  TYPE_3__ printTableContent ;
struct TYPE_7__ {int tuples_only; unsigned short border; scalar_t__ stop_table; scalar_t__ start_table; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ cancel_pressed ; 
 TYPE_2__* footers_with_default (TYPE_3__ const*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  latex_escaped_print (char const* const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_latex_text(const printTableContent *cont, FILE *fout)
{
	bool		opt_tuples_only = cont->opt->tuples_only;
	unsigned short opt_border = cont->opt->border;
	unsigned int i;
	const char *const *ptr;

	if (cancel_pressed)
		return;

	if (opt_border > 3)
		opt_border = 3;

	if (cont->opt->start_table)
	{
		/* print title */
		if (!opt_tuples_only && cont->title)
		{
			fputs("\\begin{center}\n", fout);
			latex_escaped_print(cont->title, fout);
			fputs("\n\\end{center}\n\n", fout);
		}

		/* begin environment and set alignments and borders */
		fputs("\\begin{tabular}{", fout);

		if (opt_border >= 2)
			fputs("| ", fout);
		for (i = 0; i < cont->ncolumns; i++)
		{
			fputc(*(cont->aligns + i), fout);
			if (opt_border != 0 && i < cont->ncolumns - 1)
				fputs(" | ", fout);
		}
		if (opt_border >= 2)
			fputs(" |", fout);

		fputs("}\n", fout);

		if (!opt_tuples_only && opt_border >= 2)
			fputs("\\hline\n", fout);

		/* print headers */
		if (!opt_tuples_only)
		{
			for (i = 0, ptr = cont->headers; i < cont->ncolumns; i++, ptr++)
			{
				if (i != 0)
					fputs(" & ", fout);
				fputs("\\textit{", fout);
				latex_escaped_print(*ptr, fout);
				fputc('}', fout);
			}
			fputs(" \\\\\n", fout);
			fputs("\\hline\n", fout);
		}
	}

	/* print cells */
	for (i = 0, ptr = cont->cells; *ptr; i++, ptr++)
	{
		latex_escaped_print(*ptr, fout);

		if ((i + 1) % cont->ncolumns == 0)
		{
			fputs(" \\\\\n", fout);
			if (opt_border == 3)
				fputs("\\hline\n", fout);
			if (cancel_pressed)
				break;
		}
		else
			fputs(" & ", fout);
	}

	if (cont->opt->stop_table)
	{
		printTableFooter *footers = footers_with_default(cont);

		if (opt_border == 2)
			fputs("\\hline\n", fout);

		fputs("\\end{tabular}\n\n\\noindent ", fout);

		/* print footers */
		if (footers && !opt_tuples_only && !cancel_pressed)
		{
			printTableFooter *f;

			for (f = footers; f; f = f->next)
			{
				latex_escaped_print(f->data, fout);
				fputs(" \\\\\n", fout);
			}
		}

		fputc('\n', fout);
	}
}