#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sym_hist_entry {int dummy; } ;
struct sym_hist {int dummy; } ;
struct annotated_source {size_t sizeof_sym_hist; int nr_histograms; int /*<<< orphan*/  histograms; } ;

/* Variables and functions */
 int SIZE_MAX ; 
 int /*<<< orphan*/  calloc (int,size_t) ; 

__attribute__((used)) static int annotated_source__alloc_histograms(struct annotated_source *src,
					      size_t size, int nr_hists)
{
	size_t sizeof_sym_hist;

	/*
	 * Add buffer of one element for zero length symbol.
	 * When sample is taken from first instruction of
	 * zero length symbol, perf still resolves it and
	 * shows symbol name in perf report and allows to
	 * annotate it.
	 */
	if (size == 0)
		size = 1;

	/* Check for overflow when calculating sizeof_sym_hist */
	if (size > (SIZE_MAX - sizeof(struct sym_hist)) / sizeof(struct sym_hist_entry))
		return -1;

	sizeof_sym_hist = (sizeof(struct sym_hist) + size * sizeof(struct sym_hist_entry));

	/* Check for overflow in zalloc argument */
	if (sizeof_sym_hist > SIZE_MAX / nr_hists)
		return -1;

	src->sizeof_sym_hist = sizeof_sym_hist;
	src->nr_histograms   = nr_hists;
	src->histograms	     = calloc(nr_hists, sizeof_sym_hist) ;
	return src->histograms ? 0 : -1;
}