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
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateDir (char const*) ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 struct dirent* ReadDir (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

bool
directory_is_empty(const char *path)
{
	DIR		   *dirdesc;
	struct dirent *de;

	dirdesc = AllocateDir(path);

	while ((de = ReadDir(dirdesc, path)) != NULL)
	{
		if (strcmp(de->d_name, ".") == 0 ||
			strcmp(de->d_name, "..") == 0)
			continue;
		FreeDir(dirdesc);
		return false;
	}

	FreeDir(dirdesc);
	return true;
}