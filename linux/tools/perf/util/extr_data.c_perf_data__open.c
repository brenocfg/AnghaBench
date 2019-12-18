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
struct perf_data {char* path; int /*<<< orphan*/  is_dir; } ;

/* Variables and functions */
 scalar_t__ check_backup (struct perf_data*) ; 
 scalar_t__ check_pipe (struct perf_data*) ; 
 int /*<<< orphan*/  is_dir (struct perf_data*) ; 
 int open_dir (struct perf_data*) ; 
 int open_file_dup (struct perf_data*) ; 
 scalar_t__ perf_data__is_dir (struct perf_data*) ; 
 scalar_t__ perf_data__is_read (struct perf_data*) ; 

int perf_data__open(struct perf_data *data)
{
	if (check_pipe(data))
		return 0;

	if (!data->path)
		data->path = "perf.data";

	if (check_backup(data))
		return -1;

	if (perf_data__is_read(data))
		data->is_dir = is_dir(data);

	return perf_data__is_dir(data) ?
	       open_dir(data) : open_file_dup(data);
}