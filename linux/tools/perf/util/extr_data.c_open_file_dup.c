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
struct perf_data {TYPE_1__ file; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int ENOMEM ; 
 int open_file (struct perf_data*) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int open_file_dup(struct perf_data *data)
{
	data->file.path = strdup(data->path);
	if (!data->file.path)
		return -ENOMEM;

	return open_file(data);
}