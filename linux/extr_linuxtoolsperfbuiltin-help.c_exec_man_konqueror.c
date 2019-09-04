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
 int /*<<< orphan*/  exec_failed (char const*) ; 
 int /*<<< orphan*/  execlp (char const*,char const*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char const*) ; 
 void* strrchr (char const*,char) ; 

__attribute__((used)) static void exec_man_konqueror(const char *path, const char *page)
{
	const char *display = getenv("DISPLAY");

	if (display && *display) {
		char *man_page;
		const char *filename = "kfmclient";

		/* It's simpler to launch konqueror using kfmclient. */
		if (path) {
			const char *file = strrchr(path, '/');
			if (file && !strcmp(file + 1, "konqueror")) {
				char *new = strdup(path);
				char *dest = strrchr(new, '/');

				/* strlen("konqueror") == strlen("kfmclient") */
				strcpy(dest + 1, "kfmclient");
				path = new;
			}
			if (file)
				filename = file;
		} else
			path = "kfmclient";
		if (asprintf(&man_page, "man:%s(1)", page) > 0) {
			execlp(path, filename, "newTab", man_page, NULL);
			free(man_page);
		}
		exec_failed(path);
	}
}