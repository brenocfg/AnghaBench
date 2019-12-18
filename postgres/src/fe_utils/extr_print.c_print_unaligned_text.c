#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char const* const data; struct TYPE_9__* next; } ;
typedef  TYPE_2__ printTableFooter ;
struct TYPE_10__ {char const* const title; char** headers; char** cells; unsigned int ncolumns; TYPE_1__* opt; } ;
typedef  TYPE_3__ printTableContent ;
struct TYPE_11__ {scalar_t__ separator_zero; } ;
struct TYPE_8__ {int tuples_only; TYPE_5__ recordSep; scalar_t__ stop_table; TYPE_5__ fieldSep; scalar_t__ start_table; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ cancel_pressed ; 
 TYPE_2__* footers_with_default (TYPE_3__ const*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char const* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_separator (TYPE_5__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_unaligned_text(const printTableContent *cont, FILE *fout)
{
	bool		opt_tuples_only = cont->opt->tuples_only;
	unsigned int i;
	const char *const *ptr;
	bool		need_recordsep = false;

	if (cancel_pressed)
		return;

	if (cont->opt->start_table)
	{
		/* print title */
		if (!opt_tuples_only && cont->title)
		{
			fputs(cont->title, fout);
			print_separator(cont->opt->recordSep, fout);
		}

		/* print headers */
		if (!opt_tuples_only)
		{
			for (ptr = cont->headers; *ptr; ptr++)
			{
				if (ptr != cont->headers)
					print_separator(cont->opt->fieldSep, fout);
				fputs(*ptr, fout);
			}
			need_recordsep = true;
		}
	}
	else
		/* assume continuing printout */
		need_recordsep = true;

	/* print cells */
	for (i = 0, ptr = cont->cells; *ptr; i++, ptr++)
	{
		if (need_recordsep)
		{
			print_separator(cont->opt->recordSep, fout);
			need_recordsep = false;
			if (cancel_pressed)
				break;
		}
		fputs(*ptr, fout);

		if ((i + 1) % cont->ncolumns)
			print_separator(cont->opt->fieldSep, fout);
		else
			need_recordsep = true;
	}

	/* print footers */
	if (cont->opt->stop_table)
	{
		printTableFooter *footers = footers_with_default(cont);

		if (!opt_tuples_only && footers != NULL && !cancel_pressed)
		{
			printTableFooter *f;

			for (f = footers; f; f = f->next)
			{
				if (need_recordsep)
				{
					print_separator(cont->opt->recordSep, fout);
					need_recordsep = false;
				}
				fputs(f->data, fout);
				need_recordsep = true;
			}
		}

		/*
		 * The last record is terminated by a newline, independent of the set
		 * record separator.  But when the record separator is a zero byte, we
		 * use that (compatible with find -print0 and xargs).
		 */
		if (need_recordsep)
		{
			if (cont->opt->recordSep.separator_zero)
				print_separator(cont->opt->recordSep, fout);
			else
				fputc('\n', fout);
		}
	}
}