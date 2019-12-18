#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char** headers; char** cells; int ncolumns; TYPE_1__* opt; } ;
typedef  TYPE_2__ printTableContent ;
struct TYPE_4__ {char* csvFieldSep; int /*<<< orphan*/  tuples_only; scalar_t__ start_table; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ cancel_pressed ; 
 int /*<<< orphan*/  csv_print_field (char const* const,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_csv_text(const printTableContent *cont, FILE *fout)
{
	const char *const *ptr;
	int			i;

	if (cancel_pressed)
		return;

	/*
	 * The title and footer are never printed in csv format. The header is
	 * printed if opt_tuples_only is false.
	 *
	 * Despite RFC 4180 saying that end of lines are CRLF, terminate lines
	 * with '\n', which prints out as the system-dependent EOL string in text
	 * mode (typically LF on Unix and CRLF on Windows).
	 */
	if (cont->opt->start_table && !cont->opt->tuples_only)
	{
		/* print headers */
		for (ptr = cont->headers; *ptr; ptr++)
		{
			if (ptr != cont->headers)
				fputc(cont->opt->csvFieldSep[0], fout);
			csv_print_field(*ptr, fout, cont->opt->csvFieldSep[0]);
		}
		fputc('\n', fout);
	}

	/* print cells */
	for (i = 0, ptr = cont->cells; *ptr; i++, ptr++)
	{
		csv_print_field(*ptr, fout, cont->opt->csvFieldSep[0]);
		if ((i + 1) % cont->ncolumns)
			fputc(cont->opt->csvFieldSep[0], fout);
		else
			fputc('\n', fout);
	}
}