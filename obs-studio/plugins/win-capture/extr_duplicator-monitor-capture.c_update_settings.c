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
struct duplicator_capture {int monitor; float reset_timeout; scalar_t__ rot; scalar_t__ y; scalar_t__ x; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/ * duplicator; int /*<<< orphan*/  capture_cursor; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_duplicator_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_get_bool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 

__attribute__((used)) static inline void update_settings(struct duplicator_capture *capture,
				   obs_data_t *settings)
{
	capture->monitor = (int)obs_data_get_int(settings, "monitor");
	capture->capture_cursor = obs_data_get_bool(settings, "capture_cursor");

	obs_enter_graphics();

	gs_duplicator_destroy(capture->duplicator);
	capture->duplicator = NULL;
	capture->width = 0;
	capture->height = 0;
	capture->x = 0;
	capture->y = 0;
	capture->rot = 0;
	capture->reset_timeout = 0.0f;

	obs_leave_graphics();
}