#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  new_link_file ;
typedef  int /*<<< orphan*/  existing_file ;
struct TYPE_4__ {char* pgdata; } ;
struct TYPE_3__ {char* pgdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPYFILE_CLONE_FORCE ; 
 int /*<<< orphan*/  FICLONE ; 
 int MAXPGPATH ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ copyfile (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ new_cluster ; 
 TYPE_1__ old_cluster ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_fatal (char*,...) ; 
 int /*<<< orphan*/  pg_file_create_mode ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void
check_file_clone(void)
{
	char		existing_file[MAXPGPATH];
	char		new_link_file[MAXPGPATH];

	snprintf(existing_file, sizeof(existing_file), "%s/PG_VERSION", old_cluster.pgdata);
	snprintf(new_link_file, sizeof(new_link_file), "%s/PG_VERSION.clonetest", new_cluster.pgdata);
	unlink(new_link_file);		/* might fail */

#if defined(HAVE_COPYFILE) && defined(COPYFILE_CLONE_FORCE)
	if (copyfile(existing_file, new_link_file, NULL, COPYFILE_CLONE_FORCE) < 0)
		pg_fatal("could not clone file between old and new data directories: %s\n",
				 strerror(errno));
#elif defined(__linux__) && defined(FICLONE)
	{
		int			src_fd;
		int			dest_fd;

		if ((src_fd = open(existing_file, O_RDONLY | PG_BINARY, 0)) < 0)
			pg_fatal("could not open file \"%s\": %s\n",
					 existing_file, strerror(errno));

		if ((dest_fd = open(new_link_file, O_RDWR | O_CREAT | O_EXCL | PG_BINARY,
							pg_file_create_mode)) < 0)
			pg_fatal("could not create file \"%s\": %s\n",
					 new_link_file, strerror(errno));

		if (ioctl(dest_fd, FICLONE, src_fd) < 0)
			pg_fatal("could not clone file between old and new data directories: %s\n",
					 strerror(errno));

		close(src_fd);
		close(dest_fd);
	}
#else
	pg_fatal("file cloning not supported on this platform\n");
#endif

	unlink(new_link_file);
}