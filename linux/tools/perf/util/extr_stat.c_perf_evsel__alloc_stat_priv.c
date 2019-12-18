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
struct perf_stat_evsel {int dummy; } ;
struct evsel {int /*<<< orphan*/ * stats; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  perf_evsel__reset_stat_priv (struct evsel*) ; 
 int /*<<< orphan*/ * zalloc (int) ; 

__attribute__((used)) static int perf_evsel__alloc_stat_priv(struct evsel *evsel)
{
	evsel->stats = zalloc(sizeof(struct perf_stat_evsel));
	if (evsel->stats == NULL)
		return -ENOMEM;
	perf_evsel__reset_stat_priv(evsel);
	return 0;
}