#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  printTableOpt ;
struct TYPE_3__ {char const* title; int ncolumns; int nrows; scalar_t__ cellsadded; void* aligns; void* align; int /*<<< orphan*/ * footers; int /*<<< orphan*/ * footer; void* cells; void* cell; void* headers; void* header; int /*<<< orphan*/ * cellmustfree; int /*<<< orphan*/  const* opt; } ;
typedef  TYPE_1__ printTableContent ;

/* Variables and functions */
 void* pg_malloc0 (int const) ; 

void
printTableInit(printTableContent *const content, const printTableOpt *opt,
			   const char *title, const int ncolumns, const int nrows)
{
	content->opt = opt;
	content->title = title;
	content->ncolumns = ncolumns;
	content->nrows = nrows;

	content->headers = pg_malloc0((ncolumns + 1) * sizeof(*content->headers));

	content->cells = pg_malloc0((ncolumns * nrows + 1) * sizeof(*content->cells));

	content->cellmustfree = NULL;
	content->footers = NULL;

	content->aligns = pg_malloc0((ncolumns + 1) * sizeof(*content->align));

	content->header = content->headers;
	content->cell = content->cells;
	content->footer = content->footers;
	content->align = content->aligns;
	content->cellsadded = 0;
}