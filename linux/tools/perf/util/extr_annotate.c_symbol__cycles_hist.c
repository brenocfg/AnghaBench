#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symbol {int dummy; } ;
struct cyc_hist {int dummy; } ;
struct annotation {TYPE_1__* src; } ;
struct TYPE_2__ {struct cyc_hist* cycles_hist; } ;

/* Variables and functions */
 TYPE_1__* annotated_source__new () ; 
 int /*<<< orphan*/  symbol__alloc_hist_cycles (struct symbol*) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 

__attribute__((used)) static struct cyc_hist *symbol__cycles_hist(struct symbol *sym)
{
	struct annotation *notes = symbol__annotation(sym);

	if (notes->src == NULL) {
		notes->src = annotated_source__new();
		if (notes->src == NULL)
			return NULL;
		goto alloc_cycles_hist;
	}

	if (!notes->src->cycles_hist) {
alloc_cycles_hist:
		symbol__alloc_hist_cycles(sym);
	}

	return notes->src->cycles_hist;
}