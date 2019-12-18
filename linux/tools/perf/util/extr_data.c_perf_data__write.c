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
struct perf_data {int /*<<< orphan*/  file; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  perf_data_file__write (int /*<<< orphan*/ *,void*,size_t) ; 

ssize_t perf_data__write(struct perf_data *data,
			      void *buf, size_t size)
{
	return perf_data_file__write(&data->file, buf, size);
}