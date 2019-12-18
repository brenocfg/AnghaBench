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
struct dirent {scalar_t__ d_type; int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE_FILES ; 
 scalar_t__ DT_DIR ; 
 scalar_t__ DT_LNK ; 
 int O_DIRECTORY ; 
 int O_PATH ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (unsigned int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 unsigned int dirfd (int /*<<< orphan*/ *) ; 
 unsigned int dup2 (unsigned int,unsigned int) ; 
 unsigned int open (char*,int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int streq (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_lookup (unsigned int) ; 
 int unshare (int /*<<< orphan*/ ) ; 
 struct dirent* xreaddir (int /*<<< orphan*/ *) ; 
 unsigned long long xstrtoull (int /*<<< orphan*/ ,char**) ; 

int main(void)
{
	struct dirent *de;
	unsigned int fd, target_fd;

	if (unshare(CLONE_FILES) == -1)
		return 1;

	/* Wipe fdtable. */
	do {
		DIR *d;

		d = opendir("/proc/self/fd");
		if (!d)
			return 1;

		de = xreaddir(d);
		assert(de->d_type == DT_DIR);
		assert(streq(de->d_name, "."));

		de = xreaddir(d);
		assert(de->d_type == DT_DIR);
		assert(streq(de->d_name, ".."));
next:
		de = xreaddir(d);
		if (de) {
			unsigned long long fd_ull;
			unsigned int fd;
			char *end;

			assert(de->d_type == DT_LNK);

			fd_ull = xstrtoull(de->d_name, &end);
			assert(*end == '\0');
			assert(fd_ull == (unsigned int)fd_ull);

			fd = fd_ull;
			if (fd == dirfd(d))
				goto next;
			close(fd);
		}

		closedir(d);
	} while (de);

	/* Now fdtable is clean. */

	fd = open("/", O_PATH|O_DIRECTORY);
	assert(fd == 0);
	test_lookup(fd);
	close(fd);

	/* Clean again! */

	fd = open("/", O_PATH|O_DIRECTORY);
	assert(fd == 0);
	/* Default RLIMIT_NOFILE-1 */
	target_fd = 1023;
	while (target_fd > 0) {
		if (dup2(fd, target_fd) == target_fd)
			break;
		target_fd /= 2;
	}
	assert(target_fd > 0);
	close(fd);
	test_lookup(target_fd);
	close(target_fd);

	return 0;
}