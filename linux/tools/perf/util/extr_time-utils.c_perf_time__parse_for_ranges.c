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
struct perf_time_interval {int dummy; } ;
struct perf_session {TYPE_1__* evlist; } ;
struct TYPE_2__ {int /*<<< orphan*/  last_sample_time; int /*<<< orphan*/  first_sample_time; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  free (struct perf_time_interval*) ; 
 int perf_time__parse_strs (struct perf_time_interval*,char const*,int) ; 
 int perf_time__percent_parse_str (struct perf_time_interval*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct perf_time_interval* perf_time__range_alloc (char const*,int*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int strchr (char const*,char) ; 

int perf_time__parse_for_ranges(const char *time_str,
				struct perf_session *session,
				struct perf_time_interval **ranges,
				int *range_size, int *range_num)
{
	bool has_percent = strchr(time_str, '%');
	struct perf_time_interval *ptime_range;
	int size, num, ret = -EINVAL;

	ptime_range = perf_time__range_alloc(time_str, &size);
	if (!ptime_range)
		return -ENOMEM;

	if (has_percent) {
		if (session->evlist->first_sample_time == 0 &&
		    session->evlist->last_sample_time == 0) {
			pr_err("HINT: no first/last sample time found in perf data.\n"
			       "Please use latest perf binary to execute 'perf record'\n"
			       "(if '--buildid-all' is enabled, please set '--timestamp-boundary').\n");
			goto error;
		}

		num = perf_time__percent_parse_str(
				ptime_range, size,
				time_str,
				session->evlist->first_sample_time,
				session->evlist->last_sample_time);
	} else {
		num = perf_time__parse_strs(ptime_range, time_str, size);
	}

	if (num < 0)
		goto error_invalid;

	*range_size = size;
	*range_num = num;
	*ranges = ptime_range;
	return 0;

error_invalid:
	pr_err("Invalid time string\n");
error:
	free(ptime_range);
	return ret;
}