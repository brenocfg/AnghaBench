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
struct mntent {int /*<<< orphan*/  mnt_dir; int /*<<< orphan*/  mnt_type; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 struct mntent* getmntent (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *find_cgroup_root(void)
{
	struct mntent *mnt;
	FILE *f;

	f = fopen("/proc/mounts", "r");
	if (f == NULL)
		return NULL;

	while ((mnt = getmntent(f))) {
		if (strcmp(mnt->mnt_type, "cgroup2") == 0) {
			fclose(f);
			return strdup(mnt->mnt_dir);
		}
	}

	fclose(f);
	return NULL;
}