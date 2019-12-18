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
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTDIR ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_fatal (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

bool
pid_lock_file_exists(const char *datadir)
{
	char		path[MAXPGPATH];
	int			fd;

	snprintf(path, sizeof(path), "%s/postmaster.pid", datadir);

	if ((fd = open(path, O_RDONLY, 0)) < 0)
	{
		/* ENOTDIR means we will throw a more useful error later */
		if (errno != ENOENT && errno != ENOTDIR)
			pg_fatal("could not open file \"%s\" for reading: %s\n",
					 path, strerror(errno));

		return false;
	}

	close(fd);
	return true;
}