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

/* Variables and functions */
 int /*<<< orphan*/  PERF_MAN_PATH ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  system_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_man_path(void)
{
	char *new_path;
	const char *old_path = getenv("MANPATH");

	/* We should always put ':' after our path. If there is no
	 * old_path, the ':' at the end will let 'man' to try
	 * system-wide paths after ours to find the manual page. If
	 * there is old_path, we need ':' as delimiter. */
	if (asprintf(&new_path, "%s:%s", system_path(PERF_MAN_PATH), old_path ?: "") > 0) {
		setenv("MANPATH", new_path, 1);
		free(new_path);
	} else {
		pr_err("Unable to setup man path");
	}
}