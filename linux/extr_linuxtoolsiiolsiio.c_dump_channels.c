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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ check_postfix (char*,char*) ; 
 scalar_t__ check_prefix (char*,char*) ; 
 int closedir (int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dump_channels(const char *dev_dir_name)
{
	DIR *dp;
	const struct dirent *ent;

	dp = opendir(dev_dir_name);
	if (!dp)
		return -errno;

	while (ent = readdir(dp), ent)
		if (check_prefix(ent->d_name, "in_") &&
		   (check_postfix(ent->d_name, "_raw") ||
		    check_postfix(ent->d_name, "_input")))
			printf("   %-10s\n", ent->d_name);

	return (closedir(dp) == -1) ? -errno : 0;
}