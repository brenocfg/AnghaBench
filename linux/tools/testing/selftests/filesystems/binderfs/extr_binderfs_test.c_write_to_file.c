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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,char const*,...) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  strerror (int) ; 
 scalar_t__ write_nointr (int,void const*,size_t) ; 

__attribute__((used)) static void write_to_file(const char *filename, const void *buf, size_t count,
			  int allowed_errno)
{
	int fd, saved_errno;
	ssize_t ret;

	fd = open(filename, O_WRONLY | O_CLOEXEC);
	if (fd < 0)
		ksft_exit_fail_msg("%s - Failed to open file %s\n",
				   strerror(errno), filename);

	ret = write_nointr(fd, buf, count);
	if (ret < 0) {
		if (allowed_errno && (errno == allowed_errno)) {
			close(fd);
			return;
		}

		goto on_error;
	}

	if ((size_t)ret != count)
		goto on_error;

	close(fd);
	return;

on_error:
	saved_errno = errno;
	close(fd);
	errno = saved_errno;

	if (ret < 0)
		ksft_exit_fail_msg("%s - Failed to write to file %s\n",
				   strerror(errno), filename);

	ksft_exit_fail_msg("Failed to write to file %s\n", filename);
}