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
struct TYPE_2__ {scalar_t__ task; scalar_t__ comm; scalar_t__ mmap2; scalar_t__ mmap; } ;
struct perf_evsel {TYPE_1__ attr; } ;

/* Variables and functions */

__attribute__((used)) static bool has_tracking(struct perf_evsel *evsel)
{
	return evsel->attr.mmap || evsel->attr.mmap2 || evsel->attr.comm ||
	       evsel->attr.task;
}