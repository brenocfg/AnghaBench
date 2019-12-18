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
 int /*<<< orphan*/  CLONE_NEWNS ; 
 scalar_t__ ELOOP ; 
 scalar_t__ ENOSYS ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  FILENAME ; 
 int MS_PRIVATE ; 
 int MS_REC ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  close (int) ; 
 int creat (int /*<<< orphan*/ ,int) ; 
 scalar_t__ errno ; 
 int execve (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int mount (int /*<<< orphan*/ *,char*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int unshare (int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,int /*<<< orphan*/ ,scalar_t__) ; 

int main(void)
{
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
	/* Require "exec" filesystem. */
	if (mount(NULL, "/tmp", "ramfs", 0, NULL) == -1) {
		fprintf(stderr, "error: mount ramfs, errno %d\n", errno);
		return 1;
	}

#define FILENAME "/tmp/1"

	int fd = creat(FILENAME, 0700);
	if (fd == -1) {
		fprintf(stderr, "error: creat, errno %d\n", errno);
		return 1;
	}
#define S "#!" FILENAME "\n"
	if (write(fd, S, strlen(S)) != strlen(S)) {
		fprintf(stderr, "error: write, errno %d\n", errno);
		return 1;
	}
	close(fd);

	int rv = execve(FILENAME, NULL, NULL);
	if (rv == -1 && errno == ELOOP) {
		return 0;
	}
	fprintf(stderr, "error: execve, rv %d, errno %d\n", rv, errno);
	return 1;
}