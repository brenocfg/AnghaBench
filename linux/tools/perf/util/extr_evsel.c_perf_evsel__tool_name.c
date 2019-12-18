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

/* Variables and functions */
 int scnprintf (char*,size_t,char*) ; 

__attribute__((used)) static int perf_evsel__tool_name(char *bf, size_t size)
{
	int ret = scnprintf(bf, size, "duration_time");
	return ret;
}