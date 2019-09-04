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
struct dstr {int /*<<< orphan*/  array; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_depad (struct dstr*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init (struct dstr*) ; 
 int /*<<< orphan*/  dstr_resize (struct dstr*,scalar_t__) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static void log_processor_info(void)
{
	int physical_id = -1;
	int last_physical_id = -1;
	char *line = NULL;
	size_t linecap = 0;

	FILE *fp;
	struct dstr proc_name;
	struct dstr proc_speed;

	fp = fopen("/proc/cpuinfo", "r");
	if (!fp)
		return;

	dstr_init(&proc_name);
	dstr_init(&proc_speed);

	while (getline(&line, &linecap, fp) != -1) {
		if (!strncmp(line, "model name", 10)) {
			char *start = strchr(line, ':');
			if (!start || *(++start) == '\0')
				continue;

			dstr_copy(&proc_name, start);
			dstr_resize(&proc_name, proc_name.len - 1);
			dstr_depad(&proc_name);
		}

		if (!strncmp(line, "physical id", 11)) {
			char *start = strchr(line, ':');
			if (!start || *(++start) == '\0')
				continue;

			physical_id = atoi(start);
		}

		if (!strncmp(line, "cpu MHz", 7)) {
			char *start = strchr(line, ':');
			if (!start || *(++start) == '\0')
				continue;

			dstr_copy(&proc_speed, start);
			dstr_resize(&proc_speed, proc_speed.len - 1);
			dstr_depad(&proc_speed);
		}

		if (*line == '\n' && physical_id != last_physical_id) {
			last_physical_id = physical_id;
			blog(LOG_INFO, "CPU Name: %s", proc_name.array);
			blog(LOG_INFO, "CPU Speed: %sMHz", proc_speed.array);
		}
	}

	fclose(fp);
	dstr_free(&proc_name);
	dstr_free(&proc_speed);
	free(line);
}