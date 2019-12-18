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
struct evsel {int dummy; } ;

/* Variables and functions */
 struct evsel* perf_evsel__new_idx (struct perf_event_attr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct evsel *evsel__new(struct perf_event_attr *attr)
{
	return perf_evsel__new_idx(attr, 0);
}