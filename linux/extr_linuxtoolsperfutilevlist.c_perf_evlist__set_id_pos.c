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
struct perf_evsel {int /*<<< orphan*/  is_pos; int /*<<< orphan*/  id_pos; } ;
struct perf_evlist {int /*<<< orphan*/  is_pos; int /*<<< orphan*/  id_pos; } ;

/* Variables and functions */
 struct perf_evsel* perf_evlist__first (struct perf_evlist*) ; 

void perf_evlist__set_id_pos(struct perf_evlist *evlist)
{
	struct perf_evsel *first = perf_evlist__first(evlist);

	evlist->id_pos = first->id_pos;
	evlist->is_pos = first->is_pos;
}