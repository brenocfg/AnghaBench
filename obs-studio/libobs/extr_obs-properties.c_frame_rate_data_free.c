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
struct frame_rate_data {int /*<<< orphan*/  ranges; int /*<<< orphan*/  extra_options; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_rate_data_options_free (struct frame_rate_data*) ; 
 int /*<<< orphan*/  frame_rate_data_ranges_free (struct frame_rate_data*) ; 

__attribute__((used)) static inline void frame_rate_data_free(struct frame_rate_data *data)
{
	frame_rate_data_options_free(data);
	frame_rate_data_ranges_free(data);

	da_free(data->extra_options);
	da_free(data->ranges);
}