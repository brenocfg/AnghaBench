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
 int /*<<< orphan*/  memset (struct perf_time_interval*,int /*<<< orphan*/ ,int) ; 
 int one_percent_convert (struct perf_time_interval*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int percent_comma_split (struct perf_time_interval*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percent_dash_split ; 
 int /*<<< orphan*/  percent_slash_split ; 
 char* strchr (char const*,char) ; 

int perf_time__percent_parse_str(struct perf_time_interval *ptime_buf, int num,
				 const char *ostr, u64 start, u64 end)
{
	char *c;

	/*
	 * ostr example:
	 * 10%/2,10%/3: select the second 10% slice and the third 10% slice
	 * 0%-10%,30%-40%: multiple time range
	 * 50%: just one percent
	 */

	memset(ptime_buf, 0, sizeof(*ptime_buf) * num);

	c = strchr(ostr, '/');
	if (c) {
		return percent_comma_split(ptime_buf, num, ostr, start,
					   end, percent_slash_split);
	}

	c = strchr(ostr, '-');
	if (c) {
		return percent_comma_split(ptime_buf, num, ostr, start,
					   end, percent_dash_split);
	}

	c = strchr(ostr, '%');
	if (c)
		return one_percent_convert(ptime_buf, ostr, start, end, c);

	return -1;
}