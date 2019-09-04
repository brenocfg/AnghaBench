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
struct TYPE_2__ {char* path; } ;
struct perf_data {TYPE_1__ file; } ;

/* Variables and functions */
 scalar_t__ check_pipe (struct perf_data*) ; 
 int open_file (struct perf_data*) ; 

int perf_data__open(struct perf_data *data)
{
	if (check_pipe(data))
		return 0;

	if (!data->file.path)
		data->file.path = "perf.data";

	return open_file(data);
}