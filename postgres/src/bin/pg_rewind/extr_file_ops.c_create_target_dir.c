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
typedef  int /*<<< orphan*/  dstpath ;

/* Variables and functions */
 int MAXPGPATH ; 
 char* datadir_target ; 
 scalar_t__ dry_run ; 
 scalar_t__ mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_dir_create_mode ; 
 int /*<<< orphan*/  pg_fatal (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 

__attribute__((used)) static void
create_target_dir(const char *path)
{
	char		dstpath[MAXPGPATH];

	if (dry_run)
		return;

	snprintf(dstpath, sizeof(dstpath), "%s/%s", datadir_target, path);
	if (mkdir(dstpath, pg_dir_create_mode) != 0)
		pg_fatal("could not create directory \"%s\": %m",
				 dstpath);
}