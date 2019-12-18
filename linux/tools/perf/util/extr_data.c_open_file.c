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
struct TYPE_2__ {int fd; int /*<<< orphan*/  path; } ;
struct perf_data {TYPE_1__ file; } ;

/* Variables and functions */
 int open_file_read (struct perf_data*) ; 
 int open_file_write (struct perf_data*) ; 
 scalar_t__ perf_data__is_read (struct perf_data*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int open_file(struct perf_data *data)
{
	int fd;

	fd = perf_data__is_read(data) ?
	     open_file_read(data) : open_file_write(data);

	if (fd < 0) {
		zfree(&data->file.path);
		return -1;
	}

	data->file.fd = fd;
	return 0;
}