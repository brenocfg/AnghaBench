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
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 int /*<<< orphan*/  printwarn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool xdiraccess(const char *path)
{
	DIR *dirp = opendir(path);

	if (!dirp) {
		printwarn(NULL);
		return FALSE;
	}

	closedir(dirp);
	return TRUE;
}