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
struct perf_data {int /*<<< orphan*/  path; TYPE_1__ file; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRWXU ; 
 scalar_t__ asprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mkdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open_file (struct perf_data*) ; 
 scalar_t__ perf_data__is_write (struct perf_data*) ; 
 int /*<<< orphan*/  rm_rf_perf_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int open_dir(struct perf_data *data)
{
	int ret;

	/*
	 * So far we open only the header, so we can read the data version and
	 * layout.
	 */
	if (asprintf(&data->file.path, "%s/header", data->path) < 0)
		return -1;

	if (perf_data__is_write(data) &&
	    mkdir(data->path, S_IRWXU) < 0)
		return -1;

	ret = open_file(data);

	/* Cleanup whatever we managed to create so far. */
	if (ret && perf_data__is_write(data))
		rm_rf_perf_data(data->path);

	return ret;
}