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
struct stat {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_argv_exec_path () ; 
 int /*<<< orphan*/  lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  scnprintf (char*,size_t,char*,char const*) ; 

__attribute__((used)) static const char *shell_tests__dir(char *path, size_t size)
{
	const char *devel_dirs[] = { "./tools/perf/tests", "./tests", };
        char *exec_path;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(devel_dirs); ++i) {
		struct stat st;
		if (!lstat(devel_dirs[i], &st)) {
			scnprintf(path, size, "%s/shell", devel_dirs[i]);
			if (!lstat(devel_dirs[i], &st))
				return path;
		}
	}

        /* Then installed path. */
        exec_path = get_argv_exec_path();
        scnprintf(path, size, "%s/tests/shell", exec_path);
	free(exec_path);
	return path;
}