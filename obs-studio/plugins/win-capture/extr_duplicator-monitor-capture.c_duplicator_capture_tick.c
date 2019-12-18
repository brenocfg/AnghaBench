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
struct duplicator_capture {int showing; float reset_timeout; scalar_t__ width; scalar_t__ duplicator; int /*<<< orphan*/  cursor_data; scalar_t__ capture_cursor; int /*<<< orphan*/  monitor; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 float RESET_INTERVAL_SEC ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (float) ; 
 int /*<<< orphan*/  cursor_capture (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_capture_data (struct duplicator_capture*) ; 
 scalar_t__ gs_duplicator_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_duplicator_update_frame (scalar_t__) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 int /*<<< orphan*/  obs_source_showing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_capture_data (struct duplicator_capture*) ; 

__attribute__((used)) static void duplicator_capture_tick(void *data, float seconds)
{
	struct duplicator_capture *capture = data;

	/* completely shut down monitor capture if not in use, otherwise it can
	 * sometimes generate system lag when a game is in fullscreen mode */
	if (!obs_source_showing(capture->source)) {
		if (capture->showing) {
			obs_enter_graphics();
			free_capture_data(capture);
			obs_leave_graphics();

			capture->showing = false;
		}
		return;

		/* always try to load the capture immediately when the source is first
	 * shown */
	} else if (!capture->showing) {
		capture->reset_timeout = RESET_INTERVAL_SEC;
	}

	obs_enter_graphics();

	if (!capture->duplicator) {
		capture->reset_timeout += seconds;

		if (capture->reset_timeout >= RESET_INTERVAL_SEC) {
			capture->duplicator =
				gs_duplicator_create(capture->monitor);

			capture->reset_timeout = 0.0f;
		}
	}

	if (!!capture->duplicator) {
		if (capture->capture_cursor)
			cursor_capture(&capture->cursor_data);

		if (!gs_duplicator_update_frame(capture->duplicator)) {
			free_capture_data(capture);

		} else if (capture->width == 0) {
			reset_capture_data(capture);
		}
	}

	obs_leave_graphics();

	if (!capture->showing)
		capture->showing = true;

	UNUSED_PARAMETER(seconds);
}