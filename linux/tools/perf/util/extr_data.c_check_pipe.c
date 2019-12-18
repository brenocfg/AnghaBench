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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_2__ {int fd; } ;
struct perf_data {int is_pipe; TYPE_1__ file; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 scalar_t__ perf_data__is_read (struct perf_data*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool check_pipe(struct perf_data *data)
{
	struct stat st;
	bool is_pipe = false;
	int fd = perf_data__is_read(data) ?
		 STDIN_FILENO : STDOUT_FILENO;

	if (!data->path) {
		if (!fstat(fd, &st) && S_ISFIFO(st.st_mode))
			is_pipe = true;
	} else {
		if (!strcmp(data->path, "-"))
			is_pipe = true;
	}

	if (is_pipe)
		data->file.fd = fd;

	return data->is_pipe = is_pipe;
}