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
struct TYPE_2__ {int /*<<< orphan*/  path; } ;
struct perf_data {TYPE_1__ file; } ;
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int STRERR_BUFSIZE ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  errno ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_error_r (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int open_file_write(struct perf_data *data)
{
	int fd;
	char sbuf[STRERR_BUFSIZE];

	fd = open(data->file.path, O_CREAT|O_RDWR|O_TRUNC|O_CLOEXEC,
		  S_IRUSR|S_IWUSR);

	if (fd < 0)
		pr_err("failed to open %s : %s\n", data->file.path,
			str_error_r(errno, sbuf, sizeof(sbuf)));

	return fd;
}