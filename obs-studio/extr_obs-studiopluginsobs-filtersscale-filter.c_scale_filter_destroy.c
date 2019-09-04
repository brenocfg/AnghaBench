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
struct scale_filter_data {int /*<<< orphan*/  point_sampler; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (void*) ; 
 int /*<<< orphan*/  gs_samplerstate_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 

__attribute__((used)) static void scale_filter_destroy(void *data)
{
	struct scale_filter_data *filter = data;

	obs_enter_graphics();
	gs_samplerstate_destroy(filter->point_sampler);
	obs_leave_graphics();
	bfree(data);
}