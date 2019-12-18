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
struct perf_time_interval {int dummy; } ;

/* Variables and functions */
 scalar_t__ parse_percent (double*,char*) ; 
 int set_percent_time (struct perf_time_interval*,double,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static int percent_slash_split(char *str, struct perf_time_interval *ptime,
			       u64 start, u64 end)
{
	char *p, *end_str;
	double pcnt, start_pcnt, end_pcnt;
	int i;

	/*
	 * Example:
	 * 10%/2: select the second 10% slice and the third 10% slice
	 */

	/* We can modify this string since the original one is copied */
	p = strchr(str, '/');
	if (!p)
		return -1;

	*p = '\0';
	if (parse_percent(&pcnt, str) < 0)
		return -1;

	p++;
	i = (int)strtol(p, &end_str, 10);
	if (*end_str)
		return -1;

	if (pcnt <= 0.0)
		return -1;

	start_pcnt = pcnt * (i - 1);
	end_pcnt = pcnt * i;

	return set_percent_time(ptime, start_pcnt, end_pcnt, start, end);
}