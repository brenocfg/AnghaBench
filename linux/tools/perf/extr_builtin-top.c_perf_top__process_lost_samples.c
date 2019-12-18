#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ lost; } ;
union perf_event {TYPE_2__ lost_samples; } ;
struct perf_top {int /*<<< orphan*/  lost_total; int /*<<< orphan*/  lost; } ;
struct TYPE_3__ {int /*<<< orphan*/  total_lost_samples; } ;
struct hists {TYPE_1__ stats; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 struct hists* evsel__hists (struct evsel*) ; 

__attribute__((used)) static void
perf_top__process_lost_samples(struct perf_top *top,
			       union perf_event *event,
			       struct evsel *evsel)
{
	struct hists *hists = evsel__hists(evsel);

	top->lost += event->lost_samples.lost;
	top->lost_total += event->lost_samples.lost;
	hists->stats.total_lost_samples += event->lost_samples.lost;
}