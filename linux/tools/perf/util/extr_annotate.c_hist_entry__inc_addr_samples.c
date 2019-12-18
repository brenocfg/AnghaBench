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
typedef  int /*<<< orphan*/  u64 ;
struct perf_sample {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  map; int /*<<< orphan*/  sym; } ;
struct hist_entry {TYPE_1__ ms; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 int symbol__inc_addr_samples (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct evsel*,int /*<<< orphan*/ ,struct perf_sample*) ; 

int hist_entry__inc_addr_samples(struct hist_entry *he, struct perf_sample *sample,
				 struct evsel *evsel, u64 ip)
{
	return symbol__inc_addr_samples(he->ms.sym, he->ms.map, evsel, ip, sample);
}