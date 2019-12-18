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
typedef  int /*<<< orphan*/  u64 ;
struct evsel {int dummy; } ;
typedef  enum perf_output_field { ____Placeholder_perf_output_field } perf_output_field ;

/* Variables and functions */
 int perf_evsel__do_check_stype (struct evsel*,int /*<<< orphan*/ ,char const*,int,int) ; 

__attribute__((used)) static int perf_evsel__check_stype(struct evsel *evsel,
				   u64 sample_type, const char *sample_msg,
				   enum perf_output_field field)
{
	return perf_evsel__do_check_stype(evsel, sample_type, sample_msg, field,
					  false);
}