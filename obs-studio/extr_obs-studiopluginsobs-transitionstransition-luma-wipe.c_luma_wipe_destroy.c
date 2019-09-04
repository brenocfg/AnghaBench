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
struct luma_wipe_info {int /*<<< orphan*/  wipes_list; int /*<<< orphan*/  luma_image; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct luma_wipe_info*) ; 
 int /*<<< orphan*/  gs_image_file_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 

__attribute__((used)) static void luma_wipe_destroy(void *data)
{
	struct luma_wipe_info *lwipe = data;

	obs_enter_graphics();
	gs_image_file_free(&lwipe->luma_image);
	obs_leave_graphics();

	obs_data_release(lwipe->wipes_list);

	bfree(lwipe);
}