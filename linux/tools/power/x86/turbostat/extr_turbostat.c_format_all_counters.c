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
struct thread_data {int dummy; } ;
struct pkg_data {int dummy; } ;
struct core_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  packages; int /*<<< orphan*/  cores; int /*<<< orphan*/  threads; } ;

/* Variables and functions */
 TYPE_1__ average ; 
 int /*<<< orphan*/  for_all_cpus (int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *),struct thread_data*,struct core_data*,struct pkg_data*) ; 
 int /*<<< orphan*/  format_counters (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_header (char*) ; 
 scalar_t__ summary_only ; 

void format_all_counters(struct thread_data *t, struct core_data *c, struct pkg_data *p)
{
	static int printed;

	if (!printed || !summary_only)
		print_header("\t");

	format_counters(&average.threads, &average.cores, &average.packages);

	printed = 1;

	if (summary_only)
		return;

	for_all_cpus(format_counters, t, c, p);
}