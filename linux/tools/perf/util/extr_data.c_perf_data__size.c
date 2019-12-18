#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
struct perf_data_file {scalar_t__ size; } ;
struct TYPE_4__ {int nr; struct perf_data_file* files; } ;
struct TYPE_3__ {unsigned long size; } ;
struct perf_data {TYPE_2__ dir; int /*<<< orphan*/  is_dir; TYPE_1__ file; } ;

/* Variables and functions */

unsigned long perf_data__size(struct perf_data *data)
{
	u64 size = data->file.size;
	int i;

	if (!data->is_dir)
		return size;

	for (i = 0; i < data->dir.nr; i++) {
		struct perf_data_file *file = &data->dir.files[i];

		size += file->size;
	}

	return size;
}