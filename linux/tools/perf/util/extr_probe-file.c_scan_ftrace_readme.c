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
typedef  enum ftrace_readme { ____Placeholder_ftrace_readme } ftrace_readme ;
struct TYPE_2__ {int avail; int /*<<< orphan*/  pattern; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int FTRACE_README_END ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* ftrace_readme_table ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int open_trace_file (char*,int) ; 
 int strglobmatch (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool scan_ftrace_readme(enum ftrace_readme type)
{
	int fd;
	FILE *fp;
	char *buf = NULL;
	size_t len = 0;
	bool ret = false;
	static bool scanned = false;

	if (scanned)
		goto result;

	fd = open_trace_file("README", false);
	if (fd < 0)
		return ret;

	fp = fdopen(fd, "r");
	if (!fp) {
		close(fd);
		return ret;
	}

	while (getline(&buf, &len, fp) > 0)
		for (enum ftrace_readme i = 0; i < FTRACE_README_END; i++)
			if (!ftrace_readme_table[i].avail)
				ftrace_readme_table[i].avail =
					strglobmatch(buf, ftrace_readme_table[i].pattern);
	scanned = true;

	fclose(fp);
	free(buf);

result:
	if (type >= FTRACE_README_END)
		return false;

	return ftrace_readme_table[type].avail;
}