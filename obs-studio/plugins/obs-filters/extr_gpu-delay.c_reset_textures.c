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
struct gpu_delay_filter_data {scalar_t__ interval_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_interval (struct gpu_delay_filter_data*) ; 
 int /*<<< orphan*/  free_textures (struct gpu_delay_filter_data*) ; 

__attribute__((used)) static inline void reset_textures(struct gpu_delay_filter_data *f)
{
	f->interval_ns = 0;
	free_textures(f);
	check_interval(f);
}