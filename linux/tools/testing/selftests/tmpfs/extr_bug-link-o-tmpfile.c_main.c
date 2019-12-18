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
 int /*<<< orphan*/  AT_EMPTY_PATH ; 
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  CLONE_NEWNS ; 
 scalar_t__ ENOSYS ; 
 scalar_t__ EPERM ; 
 int MS_PRIVATE ; 
 int MS_REC ; 
 int O_TMPFILE ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int linkat (int,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int mount (int /*<<< orphan*/ *,char*,char*,int,char*) ; 
 int openat (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int unshare (int /*<<< orphan*/ ) ; 

int main(void)
{
	int fd;

	if (unshare(CLONE_NEWNS) == -1) {
		if (errno == ENOSYS || errno == EPERM) {
			fprintf(stderr, "error: unshare, errno %d\n", errno);
			return 4;
		}
		fprintf(stderr, "error: unshare, errno %d\n", errno);
		return 1;
	}
	if (mount(NULL, "/", NULL, MS_PRIVATE|MS_REC, NULL) == -1) {
		fprintf(stderr, "error: mount '/', errno %d\n", errno);
		return 1;
	}

	/* Our heroes: 1 root inode, 1 O_TMPFILE inode, 1 permanent inode. */
	if (mount(NULL, "/tmp", "tmpfs", 0, "nr_inodes=3") == -1) {
		fprintf(stderr, "error: mount tmpfs, errno %d\n", errno);
		return 1;
	}

	fd = openat(AT_FDCWD, "/tmp", O_WRONLY|O_TMPFILE, 0600);
	if (fd == -1) {
		fprintf(stderr, "error: open 1, errno %d\n", errno);
		return 1;
	}
	if (linkat(fd, "", AT_FDCWD, "/tmp/1", AT_EMPTY_PATH) == -1) {
		fprintf(stderr, "error: linkat, errno %d\n", errno);
		return 1;
	}
	close(fd);

	fd = openat(AT_FDCWD, "/tmp", O_WRONLY|O_TMPFILE, 0600);
	if (fd == -1) {
		fprintf(stderr, "error: open 2, errno %d\n", errno);
		return 1;
	}

	return 0;
}