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
struct perf_event_attr {int dummy; } ;
struct perf_evsel {struct perf_event_attr attr; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

void perf_evsel__init(struct perf_evsel *evsel, struct perf_event_attr *attr)
{
	INIT_LIST_HEAD(&evsel->node);
	evsel->attr = *attr;
}