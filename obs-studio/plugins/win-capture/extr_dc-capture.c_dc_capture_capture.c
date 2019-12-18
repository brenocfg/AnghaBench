#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cbSize; } ;
struct dc_capture {int texture_written; int /*<<< orphan*/  cursor_hidden; scalar_t__ cursor_captured; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__ ci; scalar_t__ capture_cursor; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  CURSORINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetCursorInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dc_capture_get_dc (struct dc_capture*) ; 
 int /*<<< orphan*/  dc_capture_release_dc (struct dc_capture*) ; 
 int /*<<< orphan*/  draw_cursor (struct dc_capture*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void dc_capture_capture(struct dc_capture *capture, HWND window)
{
	HDC hdc_target;
	HDC hdc;

	if (capture->capture_cursor) {
		memset(&capture->ci, 0, sizeof(CURSORINFO));
		capture->ci.cbSize = sizeof(CURSORINFO);
		capture->cursor_captured = GetCursorInfo(&capture->ci);
	}

	hdc = dc_capture_get_dc(capture);
	if (!hdc) {
		blog(LOG_WARNING, "[capture_screen] Failed to get "
				  "texture DC");
		return;
	}

	hdc_target = GetDC(window);

	BitBlt(hdc, 0, 0, capture->width, capture->height, hdc_target,
	       capture->x, capture->y, SRCCOPY);

	ReleaseDC(NULL, hdc_target);

	if (capture->cursor_captured && !capture->cursor_hidden)
		draw_cursor(capture, hdc, window);

	dc_capture_release_dc(capture);

	capture->texture_written = true;
}