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
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  dstpath ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 char* datadir_target ; 
 scalar_t__ dry_run ; 
 scalar_t__ ftruncate (int,scalar_t__) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_fatal (char*,char*,...) ; 
 int /*<<< orphan*/  pg_file_create_mode ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 

void
truncate_target_file(const char *path, off_t newsize)
{
	char		dstpath[MAXPGPATH];
	int			fd;

	if (dry_run)
		return;

	snprintf(dstpath, sizeof(dstpath), "%s/%s", datadir_target, path);

	fd = open(dstpath, O_WRONLY, pg_file_create_mode);
	if (fd < 0)
		pg_fatal("could not open file \"%s\" for truncation: %m",
				 dstpath);

	if (ftruncate(fd, newsize) != 0)
		pg_fatal("could not truncate file \"%s\" to %u: %m",
				 dstpath, (unsigned int) newsize);

	close(fd);
}