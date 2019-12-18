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
struct perf_data {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ PERF_DATA_MODE_WRITE ; 

__attribute__((used)) static inline bool perf_data__is_write(struct perf_data *data)
{
	return data->mode == PERF_DATA_MODE_WRITE;
}