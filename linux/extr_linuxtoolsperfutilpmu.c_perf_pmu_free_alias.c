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
struct perf_pmu_alias {int /*<<< orphan*/  terms; int /*<<< orphan*/  metric_name; int /*<<< orphan*/  metric_expr; int /*<<< orphan*/  str; int /*<<< orphan*/  topic; int /*<<< orphan*/  long_desc; int /*<<< orphan*/  desc; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct perf_pmu_alias*) ; 
 int /*<<< orphan*/  parse_events_terms__purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void perf_pmu_free_alias(struct perf_pmu_alias *newalias)
{
	zfree(&newalias->name);
	zfree(&newalias->desc);
	zfree(&newalias->long_desc);
	zfree(&newalias->topic);
	zfree(&newalias->str);
	zfree(&newalias->metric_expr);
	zfree(&newalias->metric_name);
	parse_events_terms__purge(&newalias->terms);
	free(newalias);
}