#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fd; } ;
struct perf_data {TYPE_1__ file; int /*<<< orphan*/  path; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ check_pipe (struct perf_data*) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ lseek (int,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ perf_data__is_read (struct perf_data*) ; 
 int perf_data__open (struct perf_data*) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ rename (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strerror (int) ; 

int perf_data__switch(struct perf_data *data,
			   const char *postfix,
			   size_t pos, bool at_exit,
			   char **new_filepath)
{
	int ret;

	if (check_pipe(data))
		return -EINVAL;
	if (perf_data__is_read(data))
		return -EINVAL;

	if (asprintf(new_filepath, "%s.%s", data->path, postfix) < 0)
		return -ENOMEM;

	/*
	 * Only fire a warning, don't return error, continue fill
	 * original file.
	 */
	if (rename(data->path, *new_filepath))
		pr_warning("Failed to rename %s to %s\n", data->path, *new_filepath);

	if (!at_exit) {
		close(data->file.fd);
		ret = perf_data__open(data);
		if (ret < 0)
			goto out;

		if (lseek(data->file.fd, pos, SEEK_SET) == (off_t)-1) {
			ret = -errno;
			pr_debug("Failed to lseek to %zu: %s",
				 pos, strerror(errno));
			goto out;
		}
	}
	ret = data->file.fd;
out:
	return ret;
}