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
 scalar_t__ asprintf (char**,char*,char const*) ; 
 scalar_t__ strstarts (char const*,char*) ; 

__attribute__((used)) static const char *cmd_to_page(const char *perf_cmd)
{
	char *s;

	if (!perf_cmd)
		return "perf";
	else if (strstarts(perf_cmd, "perf"))
		return perf_cmd;

	return asprintf(&s, "perf-%s", perf_cmd) < 0 ? NULL : s;
}