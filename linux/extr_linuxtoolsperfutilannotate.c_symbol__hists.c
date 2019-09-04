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
struct symbol {int dummy; } ;
struct annotation {struct annotated_source* src; } ;
struct annotated_source {int /*<<< orphan*/ * histograms; } ;

/* Variables and functions */
 int /*<<< orphan*/  annotated_source__alloc_histograms (struct annotated_source*,int /*<<< orphan*/ ,int) ; 
 struct annotated_source* annotated_source__new () ; 
 struct annotation* symbol__annotation (struct symbol*) ; 
 int /*<<< orphan*/  symbol__size (struct symbol*) ; 

struct annotated_source *symbol__hists(struct symbol *sym, int nr_hists)
{
	struct annotation *notes = symbol__annotation(sym);

	if (notes->src == NULL) {
		notes->src = annotated_source__new();
		if (notes->src == NULL)
			return NULL;
		goto alloc_histograms;
	}

	if (notes->src->histograms == NULL) {
alloc_histograms:
		annotated_source__alloc_histograms(notes->src, symbol__size(sym),
						   nr_hists);
	}

	return notes->src;
}