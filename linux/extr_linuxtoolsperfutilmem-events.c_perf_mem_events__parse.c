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
struct perf_mem_event {int record; int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PERF_MEM_EVENTS__MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (scalar_t__) ; 
 struct perf_mem_event* perf_mem_events ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 
 char* strtok_r (char*,char*,char**) ; 

int perf_mem_events__parse(const char *str)
{
	char *tok, *saveptr = NULL;
	bool found = false;
	char *buf;
	int j;

	/* We need buffer that we know we can write to. */
	buf = malloc(strlen(str) + 1);
	if (!buf)
		return -ENOMEM;

	strcpy(buf, str);

	tok = strtok_r((char *)buf, ",", &saveptr);

	while (tok) {
		for (j = 0; j < PERF_MEM_EVENTS__MAX; j++) {
			struct perf_mem_event *e = &perf_mem_events[j];

			if (strstr(e->tag, tok))
				e->record = found = true;
		}

		tok = strtok_r(NULL, ",", &saveptr);
	}

	free(buf);

	if (found)
		return 0;

	pr_err("failed: event '%s' not found, use '-e list' to get list of available events\n", str);
	return -1;
}