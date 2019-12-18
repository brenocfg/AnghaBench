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
 int /*<<< orphan*/  perf_config_bool_or_int (char const*,char const*,int*) ; 

int perf_config_bool(const char *name, const char *value)
{
	int discard;
	return !!perf_config_bool_or_int(name, value, &discard);
}