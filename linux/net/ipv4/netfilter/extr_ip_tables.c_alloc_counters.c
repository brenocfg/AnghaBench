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
struct xt_table_info {int number; } ;
struct xt_table {struct xt_table_info* private; } ;
struct xt_counters {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct xt_counters* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_counters (struct xt_table_info const*,struct xt_counters*) ; 
 struct xt_counters* vzalloc (unsigned int) ; 

__attribute__((used)) static struct xt_counters *alloc_counters(const struct xt_table *table)
{
	unsigned int countersize;
	struct xt_counters *counters;
	const struct xt_table_info *private = table->private;

	/* We need atomic snapshot of counters: rest doesn't change
	   (other than comefrom, which userspace doesn't care
	   about). */
	countersize = sizeof(struct xt_counters) * private->number;
	counters = vzalloc(countersize);

	if (counters == NULL)
		return ERR_PTR(-ENOMEM);

	get_counters(private, counters);

	return counters;
}