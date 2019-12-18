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
struct TYPE_8__ {char* data; struct TYPE_8__* next; } ;
typedef  TYPE_2__ printTableFooter ;
struct TYPE_9__ {char* title; unsigned int ncolumns; char* aligns; char** headers; char** cells; TYPE_1__* opt; } ;
typedef  TYPE_3__ printTableContent ;
struct TYPE_7__ {int tuples_only; unsigned short border; scalar_t__ stop_table; scalar_t__ start_table; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  asciidoc_escaped_print (char const* const,int /*<<< orphan*/ *) ; 
 scalar_t__ cancel_pressed ; 
 TYPE_2__* footers_with_default (TYPE_3__ const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 size_t strspn (char const* const,char*) ; 

__attribute__((used)) static void
print_asciidoc_text(const printTableContent *cont, FILE *fout)
{
	bool		opt_tuples_only = cont->opt->tuples_only;
	unsigned short opt_border = cont->opt->border;
	unsigned int i;
	const char *const *ptr;

	if (cancel_pressed)
		return;

	if (cont->opt->start_table)
	{
		/* print table in new paragraph - enforce preliminary new line */
		fputs("\n", fout);

		/* print title */
		if (!opt_tuples_only && cont->title)
		{
			fputs(".", fout);
			fputs(cont->title, fout);
			fputs("\n", fout);
		}

		/* print table [] header definition */
		fprintf(fout, "[%scols=\"", !opt_tuples_only ? "options=\"header\"," : "");
		for (i = 0; i < cont->ncolumns; i++)
		{
			if (i != 0)
				fputs(",", fout);
			fprintf(fout, "%s", cont->aligns[(i) % cont->ncolumns] == 'r' ? ">l" : "<l");
		}
		fputs("\"", fout);
		switch (opt_border)
		{
			case 0:
				fputs(",frame=\"none\",grid=\"none\"", fout);
				break;
			case 1:
				fputs(",frame=\"none\"", fout);
				break;
			case 2:
				fputs(",frame=\"all\",grid=\"all\"", fout);
				break;
		}
		fputs("]\n", fout);
		fputs("|====\n", fout);

		/* print headers */
		if (!opt_tuples_only)
		{
			for (ptr = cont->headers; *ptr; ptr++)
			{
				if (ptr != cont->headers)
					fputs(" ", fout);
				fputs("^l|", fout);
				asciidoc_escaped_print(*ptr, fout);
			}
			fputs("\n", fout);
		}
	}

	/* print cells */
	for (i = 0, ptr = cont->cells; *ptr; i++, ptr++)
	{
		if (i % cont->ncolumns == 0)
		{
			if (cancel_pressed)
				break;
		}

		if (i % cont->ncolumns != 0)
			fputs(" ", fout);
		fputs("|", fout);

		/* protect against needless spaces */
		if ((*ptr)[strspn(*ptr, " \t")] == '\0')
		{
			if ((i + 1) % cont->ncolumns != 0)
				fputs(" ", fout);
		}
		else
			asciidoc_escaped_print(*ptr, fout);

		if ((i + 1) % cont->ncolumns == 0)
			fputs("\n", fout);
	}

	fputs("|====\n", fout);

	if (cont->opt->stop_table)
	{
		printTableFooter *footers = footers_with_default(cont);

		/* print footers */
		if (!opt_tuples_only && footers != NULL && !cancel_pressed)
		{
			printTableFooter *f;

			fputs("\n....\n", fout);
			for (f = footers; f; f = f->next)
			{
				fputs(f->data, fout);
				fputs("\n", fout);
			}
			fputs("....\n", fout);
		}
	}
}