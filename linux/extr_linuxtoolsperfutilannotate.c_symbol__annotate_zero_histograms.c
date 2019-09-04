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
struct annotation {int /*<<< orphan*/  lock; TYPE_1__* src; } ;
struct TYPE_2__ {int nr_histograms; int sizeof_sym_hist; scalar_t__ cycles_hist; scalar_t__ histograms; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 
 int symbol__size (struct symbol*) ; 

void symbol__annotate_zero_histograms(struct symbol *sym)
{
	struct annotation *notes = symbol__annotation(sym);

	pthread_mutex_lock(&notes->lock);
	if (notes->src != NULL) {
		memset(notes->src->histograms, 0,
		       notes->src->nr_histograms * notes->src->sizeof_sym_hist);
		if (notes->src->cycles_hist)
			memset(notes->src->cycles_hist, 0,
				symbol__size(sym) * sizeof(struct cyc_hist));
	}
	pthread_mutex_unlock(&notes->lock);
}