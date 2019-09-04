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
struct thread {int /*<<< orphan*/  tid; int /*<<< orphan*/  pid_; } ;
struct stat {int st_size; } ;
typedef  int /*<<< orphan*/  pathname ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  linkname ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int readlink (char*,char*,int) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ,int,...) ; 
 int trace__set_fd_pathname (struct thread*,int,char*) ; 

__attribute__((used)) static int thread__read_fd_path(struct thread *thread, int fd)
{
	char linkname[PATH_MAX], pathname[PATH_MAX];
	struct stat st;
	int ret;

	if (thread->pid_ == thread->tid) {
		scnprintf(linkname, sizeof(linkname),
			  "/proc/%d/fd/%d", thread->pid_, fd);
	} else {
		scnprintf(linkname, sizeof(linkname),
			  "/proc/%d/task/%d/fd/%d", thread->pid_, thread->tid, fd);
	}

	if (lstat(linkname, &st) < 0 || st.st_size + 1 > (off_t)sizeof(pathname))
		return -1;

	ret = readlink(linkname, pathname, sizeof(pathname));

	if (ret < 0 || ret > st.st_size)
		return -1;

	pathname[ret] = '\0';
	return trace__set_fd_pathname(thread, fd, pathname);
}