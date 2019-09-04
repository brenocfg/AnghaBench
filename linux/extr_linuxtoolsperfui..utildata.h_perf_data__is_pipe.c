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
struct perf_data {int is_pipe; } ;

/* Variables and functions */

__attribute__((used)) static inline int perf_data__is_pipe(struct perf_data *data)
{
	return data->is_pipe;
}