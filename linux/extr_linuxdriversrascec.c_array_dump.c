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
typedef  scalar_t__ u64 ;
struct seq_file {int dummy; } ;
struct ce_array {int n; int flags; int decays_done; int /*<<< orphan*/  pfns_poisoned; int /*<<< orphan*/  ces_entered; int /*<<< orphan*/ * array; } ;

/* Variables and functions */
 int /*<<< orphan*/  FULL_COUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ PFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct ce_array ce_arr ; 
 int /*<<< orphan*/  ce_mutex ; 
 int count_threshold ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int timer_interval ; 

__attribute__((used)) static int array_dump(struct seq_file *m, void *v)
{
	struct ce_array *ca = &ce_arr;
	u64 prev = 0;
	int i;

	mutex_lock(&ce_mutex);

	seq_printf(m, "{ n: %d\n", ca->n);
	for (i = 0; i < ca->n; i++) {
		u64 this = PFN(ca->array[i]);

		seq_printf(m, " %03d: [%016llx|%03llx]\n", i, this, FULL_COUNT(ca->array[i]));

		WARN_ON(prev > this);

		prev = this;
	}

	seq_printf(m, "}\n");

	seq_printf(m, "Stats:\nCEs: %llu\nofflined pages: %llu\n",
		   ca->ces_entered, ca->pfns_poisoned);

	seq_printf(m, "Flags: 0x%x\n", ca->flags);

	seq_printf(m, "Timer interval: %lld seconds\n", timer_interval);
	seq_printf(m, "Decays: %lld\n", ca->decays_done);

	seq_printf(m, "Action threshold: %d\n", count_threshold);

	mutex_unlock(&ce_mutex);

	return 0;
}