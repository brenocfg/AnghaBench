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
struct evsel {int dummy; } ;
struct TYPE_2__ {int nr; } ;

/* Variables and functions */
 TYPE_1__* evsel__cpus (struct evsel*) ; 

__attribute__((used)) static inline int perf_evsel__nr_cpus(struct evsel *evsel)
{
	return evsel__cpus(evsel)->nr;
}