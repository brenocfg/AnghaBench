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
struct mask_filter_data {int /*<<< orphan*/  image; } ;

/* Variables and functions */
 int /*<<< orphan*/  gs_image_file_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 

__attribute__((used)) static void mask_filter_image_unload(struct mask_filter_data *filter)
{
	obs_enter_graphics();
	gs_image_file_free(&filter->image);
	obs_leave_graphics();
}