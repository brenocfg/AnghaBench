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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  char DIR ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,char*) ; 
 int /*<<< orphan*/  closedir (char*) ; 
 char* get_events_file (int /*<<< orphan*/ ) ; 
 char* opendir (char*) ; 
 int /*<<< orphan*/  put_events_file (char*) ; 
 struct dirent* readdir (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 char* tracing_events__opendir () ; 

__attribute__((used)) static int count_tracepoints(void)
{
	struct dirent *events_ent;
	DIR *events_dir;
	int cnt = 0;

	events_dir = tracing_events__opendir();

	TEST_ASSERT_VAL("Can't open events dir", events_dir);

	while ((events_ent = readdir(events_dir))) {
		char *sys_path;
		struct dirent *sys_ent;
		DIR *sys_dir;

		if (!strcmp(events_ent->d_name, ".")
		    || !strcmp(events_ent->d_name, "..")
		    || !strcmp(events_ent->d_name, "enable")
		    || !strcmp(events_ent->d_name, "header_event")
		    || !strcmp(events_ent->d_name, "header_page"))
			continue;

		sys_path = get_events_file(events_ent->d_name);
		TEST_ASSERT_VAL("Can't get sys path", sys_path);

		sys_dir = opendir(sys_path);
		TEST_ASSERT_VAL("Can't open sys dir", sys_dir);

		while ((sys_ent = readdir(sys_dir))) {
			if (!strcmp(sys_ent->d_name, ".")
			    || !strcmp(sys_ent->d_name, "..")
			    || !strcmp(sys_ent->d_name, "enable")
			    || !strcmp(sys_ent->d_name, "filter"))
				continue;

			cnt++;
		}

		closedir(sys_dir);
		put_events_file(sys_path);
	}

	closedir(events_dir);
	return cnt;
}