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
struct TYPE_3__ {int /*<<< orphan*/  read_format; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID ; 
 int /*<<< orphan*/  IDENTIFIER ; 
 int /*<<< orphan*/  PERF_FORMAT_ID ; 
 int /*<<< orphan*/  perf_evsel__reset_sample_bit (struct evsel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evsel__set_sample_bit (struct evsel*,int /*<<< orphan*/ ) ; 

void perf_evsel__set_sample_id(struct evsel *evsel,
			       bool can_sample_identifier)
{
	if (can_sample_identifier) {
		perf_evsel__reset_sample_bit(evsel, ID);
		perf_evsel__set_sample_bit(evsel, IDENTIFIER);
	} else {
		perf_evsel__set_sample_bit(evsel, ID);
	}
	evsel->core.attr.read_format |= PERF_FORMAT_ID;
}