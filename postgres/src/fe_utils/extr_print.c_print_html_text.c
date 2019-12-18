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
struct TYPE_9__ {char const* const title; char** headers; char** cells; unsigned int ncolumns; char* aligns; TYPE_1__* opt; } ;
typedef  TYPE_3__ printTableContent ;
struct TYPE_7__ {int tuples_only; unsigned short border; char* tableAttr; scalar_t__ stop_table; scalar_t__ start_table; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ cancel_pressed ; 
 TYPE_2__* footers_with_default (TYPE_3__ const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  html_escaped_print (char const* const,int /*<<< orphan*/ *) ; 
 size_t strspn (char const* const,char*) ; 

__attribute__((used)) static void
print_html_text(const printTableContent *cont, FILE *fout)
{
	bool		opt_tuples_only = cont->opt->tuples_only;
	unsigned short opt_border = cont->opt->border;
	const char *opt_table_attr = cont->opt->tableAttr;
	unsigned int i;
	const char *const *ptr;

	if (cancel_pressed)
		return;

	if (cont->opt->start_table)
	{
		fprintf(fout, "<table border=\"%d\"", opt_border);
		if (opt_table_attr)
			fprintf(fout, " %s", opt_table_attr);
		fputs(">\n", fout);

		/* print title */
		if (!opt_tuples_only && cont->title)
		{
			fputs("  <caption>", fout);
			html_escaped_print(cont->title, fout);
			fputs("</caption>\n", fout);
		}

		/* print headers */
		if (!opt_tuples_only)
		{
			fputs("  <tr>\n", fout);
			for (ptr = cont->headers; *ptr; ptr++)
			{
				fputs("    <th align=\"center\">", fout);
				html_escaped_print(*ptr, fout);
				fputs("</th>\n", fout);
			}
			fputs("  </tr>\n", fout);
		}
	}

	/* print cells */
	for (i = 0, ptr = cont->cells; *ptr; i++, ptr++)
	{
		if (i % cont->ncolumns == 0)
		{
			if (cancel_pressed)
				break;
			fputs("  <tr valign=\"top\">\n", fout);
		}

		fprintf(fout, "    <td align=\"%s\">", cont->aligns[(i) % cont->ncolumns] == 'r' ? "right" : "left");
		/* is string only whitespace? */
		if ((*ptr)[strspn(*ptr, " \t")] == '\0')
			fputs("&nbsp; ", fout);
		else
			html_escaped_print(*ptr, fout);

		fputs("</td>\n", fout);

		if ((i + 1) % cont->ncolumns == 0)
			fputs("  </tr>\n", fout);
	}

	if (cont->opt->stop_table)
	{
		printTableFooter *footers = footers_with_default(cont);

		fputs("</table>\n", fout);

		/* print footers */
		if (!opt_tuples_only && footers != NULL && !cancel_pressed)
		{
			printTableFooter *f;

			fputs("<p>", fout);
			for (f = footers; f; f = f->next)
			{
				html_escaped_print(f->data, fout);
				fputs("<br />\n", fout);
			}
			fputs("</p>", fout);
		}

		fputc('\n', fout);
	}
}