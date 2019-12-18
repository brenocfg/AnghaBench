#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int ncolumns; int nrows; char* aligns; } ;
typedef  TYPE_1__ printTableContent ;
struct TYPE_13__ {scalar_t__ numericLocale; } ;
struct TYPE_12__ {int n_translate_columns; char* nullPrint; char** footers; scalar_t__* translate_columns; TYPE_4__ topt; int /*<<< orphan*/  translate_header; int /*<<< orphan*/  title; } ;
typedef  TYPE_2__ printQueryOpt ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  PQfname (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  PQftype (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/  const*,int,int) ; 
 char* PQgetvalue (int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  PQnfields (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PQntuples (int /*<<< orphan*/  const*) ; 
 scalar_t__ cancel_pressed ; 
 int /*<<< orphan*/  column_type_alignment (int /*<<< orphan*/ ) ; 
 char* format_numeric_locale (char*) ; 
 int /*<<< orphan*/  printTable (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printTableAddCell (TYPE_1__*,char*,int,int) ; 
 int /*<<< orphan*/  printTableAddFooter (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  printTableAddHeader (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printTableCleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  printTableInit (TYPE_1__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
printQuery(const PGresult *result, const printQueryOpt *opt,
		   FILE *fout, bool is_pager, FILE *flog)
{
	printTableContent cont;
	int			i,
				r,
				c;

	if (cancel_pressed)
		return;

	printTableInit(&cont, &opt->topt, opt->title,
				   PQnfields(result), PQntuples(result));

	/* Assert caller supplied enough translate_columns[] entries */
	Assert(opt->translate_columns == NULL ||
		   opt->n_translate_columns >= cont.ncolumns);

	for (i = 0; i < cont.ncolumns; i++)
	{
		printTableAddHeader(&cont, PQfname(result, i),
							opt->translate_header,
							column_type_alignment(PQftype(result, i)));
	}

	/* set cells */
	for (r = 0; r < cont.nrows; r++)
	{
		for (c = 0; c < cont.ncolumns; c++)
		{
			char	   *cell;
			bool		mustfree = false;
			bool		translate;

			if (PQgetisnull(result, r, c))
				cell = opt->nullPrint ? opt->nullPrint : "";
			else
			{
				cell = PQgetvalue(result, r, c);
				if (cont.aligns[c] == 'r' && opt->topt.numericLocale)
				{
					cell = format_numeric_locale(cell);
					mustfree = true;
				}
			}

			translate = (opt->translate_columns && opt->translate_columns[c]);
			printTableAddCell(&cont, cell, translate, mustfree);
		}
	}

	/* set footers */
	if (opt->footers)
	{
		char	  **footer;

		for (footer = opt->footers; *footer; footer++)
			printTableAddFooter(&cont, *footer);
	}

	printTable(&cont, fout, is_pager, flog);
	printTableCleanup(&cont);
}