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
struct TYPE_6__ {char const* const data; struct TYPE_6__* next; } ;
typedef  TYPE_2__ printTableFooter ;
struct TYPE_7__ {char const* const title; char** cells; unsigned int ncolumns; char const* const* headers; char* aligns; TYPE_2__* footers; TYPE_1__* opt; } ;
typedef  TYPE_3__ printTableContent ;
struct TYPE_5__ {int tuples_only; unsigned short border; char* tableAttr; int prior_records; scalar_t__ stop_table; scalar_t__ start_table; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ cancel_pressed ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  html_escaped_print (char const* const,int /*<<< orphan*/ *) ; 
 size_t strspn (char const* const,char*) ; 

__attribute__((used)) static void
print_html_vertical(const printTableContent *cont, FILE *fout)
{
	bool		opt_tuples_only = cont->opt->tuples_only;
	unsigned short opt_border = cont->opt->border;
	const char *opt_table_attr = cont->opt->tableAttr;
	unsigned long record = cont->opt->prior_records + 1;
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
	}

	/* print records */
	for (i = 0, ptr = cont->cells; *ptr; i++, ptr++)
	{
		if (i % cont->ncolumns == 0)
		{
			if (cancel_pressed)
				break;
			if (!opt_tuples_only)
				fprintf(fout,
						"\n  <tr><td colspan=\"2\" align=\"center\">Record %lu</td></tr>\n",
						record++);
			else
				fputs("\n  <tr><td colspan=\"2\">&nbsp;</td></tr>\n", fout);
		}
		fputs("  <tr valign=\"top\">\n"
			  "    <th>", fout);
		html_escaped_print(cont->headers[i % cont->ncolumns], fout);
		fputs("</th>\n", fout);

		fprintf(fout, "    <td align=\"%s\">", cont->aligns[i % cont->ncolumns] == 'r' ? "right" : "left");
		/* is string only whitespace? */
		if ((*ptr)[strspn(*ptr, " \t")] == '\0')
			fputs("&nbsp; ", fout);
		else
			html_escaped_print(*ptr, fout);

		fputs("</td>\n  </tr>\n", fout);
	}

	if (cont->opt->stop_table)
	{
		fputs("</table>\n", fout);

		/* print footers */
		if (!opt_tuples_only && cont->footers != NULL && !cancel_pressed)
		{
			printTableFooter *f;

			fputs("<p>", fout);
			for (f = cont->footers; f; f = f->next)
			{
				html_escaped_print(f->data, fout);
				fputs("<br />\n", fout);
			}
			fputs("</p>", fout);
		}

		fputc('\n', fout);
	}
}