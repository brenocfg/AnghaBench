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
typedef  char* u64 ;
struct perf_read_values {int counters_max; char** counterrawid; char** countername; int threads; char*** value; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 char** realloc (char**,int) ; 

__attribute__((used)) static int perf_read_values__enlarge_counters(struct perf_read_values *values)
{
	char **countername;
	int i, counters_max = values->counters_max * 2;
	u64 *counterrawid = realloc(values->counterrawid, counters_max * sizeof(*values->counterrawid));

	if (!counterrawid) {
		pr_debug("failed to enlarge read_values rawid array");
		goto out_enomem;
	}

	countername = realloc(values->countername, counters_max * sizeof(*values->countername));
	if (!countername) {
		pr_debug("failed to enlarge read_values rawid array");
		goto out_free_rawid;
	}

	for (i = 0; i < values->threads; i++) {
		u64 *value = realloc(values->value[i], counters_max * sizeof(**values->value));
		int j;

		if (!value) {
			pr_debug("failed to enlarge read_values ->values array");
			goto out_free_name;
		}

		for (j = values->counters_max; j < counters_max; j++)
			value[j] = 0;

		values->value[i] = value;
	}

	values->counters_max = counters_max;
	values->counterrawid = counterrawid;
	values->countername  = countername;

	return 0;
out_free_name:
	free(countername);
out_free_rawid:
	free(counterrawid);
out_enomem:
	return -ENOMEM;
}