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
 int /*<<< orphan*/  COPYFILE_CLONE_FORCE ; 
 int /*<<< orphan*/  FICLONE ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ copyfile (char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_fatal (char*,char const*,char const*,char const*,char const*,...) ; 
 int /*<<< orphan*/  pg_file_create_mode ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

void
cloneFile(const char *src, const char *dst,
		  const char *schemaName, const char *relName)
{
#if defined(HAVE_COPYFILE) && defined(COPYFILE_CLONE_FORCE)
	if (copyfile(src, dst, NULL, COPYFILE_CLONE_FORCE) < 0)
		pg_fatal("error while cloning relation \"%s.%s\" (\"%s\" to \"%s\"): %s\n",
				 schemaName, relName, src, dst, strerror(errno));
#elif defined(__linux__) && defined(FICLONE)
	int			src_fd;
	int			dest_fd;

	if ((src_fd = open(src, O_RDONLY | PG_BINARY, 0)) < 0)
		pg_fatal("error while cloning relation \"%s.%s\": could not open file \"%s\": %s\n",
				 schemaName, relName, src, strerror(errno));

	if ((dest_fd = open(dst, O_RDWR | O_CREAT | O_EXCL | PG_BINARY,
						pg_file_create_mode)) < 0)
		pg_fatal("error while cloning relation \"%s.%s\": could not create file \"%s\": %s\n",
				 schemaName, relName, dst, strerror(errno));

	if (ioctl(dest_fd, FICLONE, src_fd) < 0)
	{
		unlink(dst);
		pg_fatal("error while cloning relation \"%s.%s\" (\"%s\" to \"%s\"): %s\n",
				 schemaName, relName, src, dst, strerror(errno));
	}

	close(src_fd);
	close(dest_fd);
#endif
}