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
struct TYPE_2__ {int read_format; } ;
struct perf_evsel {TYPE_1__ attr; } ;

/* Variables and functions */
 int PERF_FORMAT_ID ; 
 scalar_t__ STAT_RECORD ; 

__attribute__((used)) static bool perf_evsel__should_store_id(struct perf_evsel *counter)
{
	return STAT_RECORD || counter->attr.read_format & PERF_FORMAT_ID;
}