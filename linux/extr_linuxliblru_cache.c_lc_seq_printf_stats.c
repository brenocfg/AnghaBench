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
struct seq_file {int dummy; } ;
struct lru_cache {int /*<<< orphan*/  changed; int /*<<< orphan*/  locked; int /*<<< orphan*/  starving; int /*<<< orphan*/  misses; int /*<<< orphan*/  hits; int /*<<< orphan*/  nr_elements; int /*<<< orphan*/  used; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lc_seq_printf_stats(struct seq_file *seq, struct lru_cache *lc)
{
	/* NOTE:
	 * total calls to lc_get are
	 * (starving + hits + misses)
	 * misses include "locked" count (update from an other thread in
	 * progress) and "changed", when this in fact lead to an successful
	 * update of the cache.
	 */
	seq_printf(seq, "\t%s: used:%u/%u hits:%lu misses:%lu starving:%lu locked:%lu changed:%lu\n",
		   lc->name, lc->used, lc->nr_elements,
		   lc->hits, lc->misses, lc->starving, lc->locked, lc->changed);
}