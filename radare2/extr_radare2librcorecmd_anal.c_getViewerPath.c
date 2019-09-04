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
 int /*<<< orphan*/  free (char*) ; 
 char* r_file_path (char const*) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static char *getViewerPath() {
	int i;
	const char *viewers[] = {
#if __WINDOWS__
		"explorer",
#else
		"open",
		"geeqie",
		"gqview",
		"eog",
		"xdg-open",
#endif
		NULL
	};
	for (i = 0; viewers[i]; i++) {
		char *viewerPath = r_file_path (viewers[i]);
		if (viewerPath && strcmp (viewerPath, viewers[i])) {
			return viewerPath;
		}
		free (viewerPath);
	}
	return NULL;
}