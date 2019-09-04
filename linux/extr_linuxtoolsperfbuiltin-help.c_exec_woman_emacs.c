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
 scalar_t__ asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  check_emacsclient_version () ; 
 int /*<<< orphan*/  exec_failed (char const*) ; 
 int /*<<< orphan*/  execlp (char const*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static void exec_woman_emacs(const char *path, const char *page)
{
	if (!check_emacsclient_version()) {
		/* This works only with emacsclient version >= 22. */
		char *man_page;

		if (!path)
			path = "emacsclient";
		if (asprintf(&man_page, "(woman \"%s\")", page) > 0) {
			execlp(path, "emacsclient", "-e", man_page, NULL);
			free(man_page);
		}
		exec_failed(path);
	}
}