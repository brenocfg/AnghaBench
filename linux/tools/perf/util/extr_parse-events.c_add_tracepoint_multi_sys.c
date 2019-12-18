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
struct parse_events_error {int dummy; } ;
struct list_head {int dummy; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int add_tracepoint_event (struct list_head*,int*,int /*<<< orphan*/ ,char const*,struct parse_events_error*,struct list_head*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strglobmatch (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  tracepoint_error (struct parse_events_error*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/ * tracing_events__opendir () ; 

__attribute__((used)) static int add_tracepoint_multi_sys(struct list_head *list, int *idx,
				    const char *sys_name, const char *evt_name,
				    struct parse_events_error *err,
				    struct list_head *head_config)
{
	struct dirent *events_ent;
	DIR *events_dir;
	int ret = 0;

	events_dir = tracing_events__opendir();
	if (!events_dir) {
		tracepoint_error(err, errno, sys_name, evt_name);
		return -1;
	}

	while (!ret && (events_ent = readdir(events_dir))) {
		if (!strcmp(events_ent->d_name, ".")
		    || !strcmp(events_ent->d_name, "..")
		    || !strcmp(events_ent->d_name, "enable")
		    || !strcmp(events_ent->d_name, "header_event")
		    || !strcmp(events_ent->d_name, "header_page"))
			continue;

		if (!strglobmatch(events_ent->d_name, sys_name))
			continue;

		ret = add_tracepoint_event(list, idx, events_ent->d_name,
					   evt_name, err, head_config);
	}

	closedir(events_dir);
	return ret;
}