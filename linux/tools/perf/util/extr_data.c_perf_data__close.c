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
struct TYPE_2__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  path; } ;
struct perf_data {TYPE_1__ file; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_data__close_dir (struct perf_data*) ; 
 scalar_t__ perf_data__is_dir (struct perf_data*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

void perf_data__close(struct perf_data *data)
{
	if (perf_data__is_dir(data))
		perf_data__close_dir(data);

	zfree(&data->file.path);
	close(data->file.fd);
}