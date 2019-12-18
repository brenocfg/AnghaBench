#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {size_t num; struct draw_callback* array; } ;
struct obs_display {int size_changed; int /*<<< orphan*/  draw_callbacks_mutex; TYPE_1__ draw_callbacks; int /*<<< orphan*/  draw_info_mutex; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; int /*<<< orphan*/  enabled; } ;
struct draw_callback {int /*<<< orphan*/  param; int /*<<< orphan*/  (* draw ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GS_DEBUG_COLOR_DISPLAY ; 
 int /*<<< orphan*/  GS_DEBUG_MARKER_BEGIN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GS_DEBUG_MARKER_END () ; 
 int /*<<< orphan*/  gs_present () ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  render_display_begin (struct obs_display*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  render_display_end () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void render_display(struct obs_display *display)
{
	uint32_t cx, cy;
	bool size_changed;

	if (!display || !display->enabled)
		return;

	GS_DEBUG_MARKER_BEGIN(GS_DEBUG_COLOR_DISPLAY, "obs_display");

	/* -------------------------------------------- */

	pthread_mutex_lock(&display->draw_info_mutex);

	cx = display->cx;
	cy = display->cy;
	size_changed = display->size_changed;

	if (size_changed)
		display->size_changed = false;

	pthread_mutex_unlock(&display->draw_info_mutex);

	/* -------------------------------------------- */

	render_display_begin(display, cx, cy, size_changed);

	pthread_mutex_lock(&display->draw_callbacks_mutex);

	for (size_t i = 0; i < display->draw_callbacks.num; i++) {
		struct draw_callback *callback;
		callback = display->draw_callbacks.array + i;

		callback->draw(callback->param, cx, cy);
	}

	pthread_mutex_unlock(&display->draw_callbacks_mutex);

	render_display_end();

	GS_DEBUG_MARKER_END();

	gs_present();
}