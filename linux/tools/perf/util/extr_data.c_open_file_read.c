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
struct stat {scalar_t__ st_uid; scalar_t__ st_size; } ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  path; } ;
struct perf_data {TYPE_1__ file; int /*<<< orphan*/  force; } ;
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int STRERR_BUFSIZE ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ geteuid () ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_error_r (int,char*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int open_file_read(struct perf_data *data)
{
	struct stat st;
	int fd;
	char sbuf[STRERR_BUFSIZE];

	fd = open(data->file.path, O_RDONLY);
	if (fd < 0) {
		int err = errno;

		pr_err("failed to open %s: %s", data->file.path,
			str_error_r(err, sbuf, sizeof(sbuf)));
		if (err == ENOENT && !strcmp(data->file.path, "perf.data"))
			pr_err("  (try 'perf record' first)");
		pr_err("\n");
		return -err;
	}

	if (fstat(fd, &st) < 0)
		goto out_close;

	if (!data->force && st.st_uid && (st.st_uid != geteuid())) {
		pr_err("File %s not owned by current user or root (use -f to override)\n",
		       data->file.path);
		goto out_close;
	}

	if (!st.st_size) {
		pr_info("zero-sized data (%s), nothing to do!\n",
			data->file.path);
		goto out_close;
	}

	data->file.size = st.st_size;
	return fd;

 out_close:
	close(fd);
	return -1;
}