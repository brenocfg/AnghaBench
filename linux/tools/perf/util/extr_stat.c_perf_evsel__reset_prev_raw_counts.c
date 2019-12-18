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
struct evsel {TYPE_2__* prev_raw_counts; } ;
struct TYPE_3__ {scalar_t__ run; scalar_t__ ena; scalar_t__ val; } ;
struct TYPE_4__ {TYPE_1__ aggr; } ;

/* Variables and functions */

__attribute__((used)) static void perf_evsel__reset_prev_raw_counts(struct evsel *evsel)
{
	if (evsel->prev_raw_counts) {
		evsel->prev_raw_counts->aggr.val = 0;
		evsel->prev_raw_counts->aggr.ena = 0;
		evsel->prev_raw_counts->aggr.run = 0;
       }
}