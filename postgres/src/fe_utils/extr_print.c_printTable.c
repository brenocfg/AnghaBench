#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_1__* opt; } ;
typedef  TYPE_2__ printTableContent ;
struct TYPE_20__ {int format; int expanded; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ClosePager (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  IsPagerNeeded (TYPE_2__ const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int*) ; 
#define  PRINT_ALIGNED 136 
#define  PRINT_ASCIIDOC 135 
#define  PRINT_CSV 134 
#define  PRINT_HTML 133 
#define  PRINT_LATEX 132 
#define  PRINT_LATEX_LONGTABLE 131 
 int PRINT_NOTHING ; 
#define  PRINT_TROFF_MS 130 
#define  PRINT_UNALIGNED 129 
#define  PRINT_WRAPPED 128 
 char* _ (char*) ; 
 scalar_t__ cancel_pressed ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  print_aligned_text (TYPE_2__ const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_aligned_vertical (TYPE_2__ const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_asciidoc_text (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_asciidoc_vertical (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_csv_text (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_csv_vertical (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_html_text (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_html_vertical (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_latex_longtable_text (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_latex_text (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_latex_vertical (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_troff_ms_text (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_troff_ms_vertical (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_unaligned_text (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_unaligned_vertical (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

void
printTable(const printTableContent *cont,
		   FILE *fout, bool is_pager, FILE *flog)
{
	bool		is_local_pager = false;

	if (cancel_pressed)
		return;

	if (cont->opt->format == PRINT_NOTHING)
		return;

	/* print_aligned_*() handle the pager themselves */
	if (!is_pager &&
		cont->opt->format != PRINT_ALIGNED &&
		cont->opt->format != PRINT_WRAPPED)
	{
		IsPagerNeeded(cont, 0, (cont->opt->expanded == 1), &fout, &is_pager);
		is_local_pager = is_pager;
	}

	/* print the stuff */

	if (flog)
		print_aligned_text(cont, flog, false);

	switch (cont->opt->format)
	{
		case PRINT_UNALIGNED:
			if (cont->opt->expanded == 1)
				print_unaligned_vertical(cont, fout);
			else
				print_unaligned_text(cont, fout);
			break;
		case PRINT_ALIGNED:
		case PRINT_WRAPPED:

			/*
			 * In expanded-auto mode, force vertical if a pager is passed in;
			 * else we may make different decisions for different hunks of the
			 * query result.
			 */
			if (cont->opt->expanded == 1 ||
				(cont->opt->expanded == 2 && is_pager))
				print_aligned_vertical(cont, fout, is_pager);
			else
				print_aligned_text(cont, fout, is_pager);
			break;
		case PRINT_CSV:
			if (cont->opt->expanded == 1)
				print_csv_vertical(cont, fout);
			else
				print_csv_text(cont, fout);
			break;
		case PRINT_HTML:
			if (cont->opt->expanded == 1)
				print_html_vertical(cont, fout);
			else
				print_html_text(cont, fout);
			break;
		case PRINT_ASCIIDOC:
			if (cont->opt->expanded == 1)
				print_asciidoc_vertical(cont, fout);
			else
				print_asciidoc_text(cont, fout);
			break;
		case PRINT_LATEX:
			if (cont->opt->expanded == 1)
				print_latex_vertical(cont, fout);
			else
				print_latex_text(cont, fout);
			break;
		case PRINT_LATEX_LONGTABLE:
			if (cont->opt->expanded == 1)
				print_latex_vertical(cont, fout);
			else
				print_latex_longtable_text(cont, fout);
			break;
		case PRINT_TROFF_MS:
			if (cont->opt->expanded == 1)
				print_troff_ms_vertical(cont, fout);
			else
				print_troff_ms_text(cont, fout);
			break;
		default:
			fprintf(stderr, _("invalid output format (internal error): %d"),
					cont->opt->format);
			exit(EXIT_FAILURE);
	}

	if (is_local_pager)
		ClosePager(fout);
}