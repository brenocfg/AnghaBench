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
struct evsel {int /*<<< orphan*/  core; int /*<<< orphan*/ * evlist; } ;
struct evlist {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_evlist__remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void evlist__remove(struct evlist *evlist, struct evsel *evsel)
{
	evsel->evlist = NULL;
	perf_evlist__remove(&evlist->core, &evsel->core);
}