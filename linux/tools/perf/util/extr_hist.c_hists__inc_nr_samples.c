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
struct TYPE_2__ {int /*<<< orphan*/  nr_non_filtered_samples; } ;
struct hists {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_RECORD_SAMPLE ; 
 int /*<<< orphan*/  events_stats__inc (TYPE_1__*,int /*<<< orphan*/ ) ; 

void hists__inc_nr_samples(struct hists *hists, bool filtered)
{
	events_stats__inc(&hists->stats, PERF_RECORD_SAMPLE);
	if (!filtered)
		hists->stats.nr_non_filtered_samples++;
}