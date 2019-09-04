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
struct gpu_delay_filter_data {int processed_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (float) ; 
 int /*<<< orphan*/  check_interval (struct gpu_delay_filter_data*) ; 
 scalar_t__ check_size (struct gpu_delay_filter_data*) ; 

__attribute__((used)) static void gpu_delay_filter_tick(void *data, float t)
{
	UNUSED_PARAMETER(t);

	struct gpu_delay_filter_data *f = data;

	f->processed_frame = false;

	if (check_size(f))
		return;
	check_interval(f);
}