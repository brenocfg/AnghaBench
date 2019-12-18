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
struct record_opts {int dummy; } ;
struct evsel {int dummy; } ;
struct callchain_param {scalar_t__ enabled; } ;

/* Variables and functions */
 void __perf_evsel__config_callchain (struct evsel*,struct record_opts*,struct callchain_param*) ; 

void perf_evsel__config_callchain(struct evsel *evsel,
				  struct record_opts *opts,
				  struct callchain_param *param)
{
	if (param->enabled)
		return __perf_evsel__config_callchain(evsel, opts, param);
}