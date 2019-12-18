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
struct perf_sample {int /*<<< orphan*/  period; int /*<<< orphan*/ * callchain; } ;
struct hist_entry {int /*<<< orphan*/  callchain; } ;
struct TYPE_2__ {int /*<<< orphan*/  show_branchflag_count; int /*<<< orphan*/  use_callchain; } ;

/* Variables and functions */
 int callchain_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callchain_cursor ; 
 TYPE_1__ symbol_conf ; 

int hist_entry__append_callchain(struct hist_entry *he, struct perf_sample *sample)
{
	if ((!symbol_conf.use_callchain || sample->callchain == NULL) &&
		!symbol_conf.show_branchflag_count)
		return 0;
	return callchain_append(he->callchain, &callchain_cursor, sample->period);
}