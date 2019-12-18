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
struct dc_capture {int /*<<< orphan*/  texture; int /*<<< orphan*/  bmp; scalar_t__ hdc; int /*<<< orphan*/  old_bmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteDC (scalar_t__) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_texture_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dc_capture*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 

void dc_capture_free(struct dc_capture *capture)
{
	if (capture->hdc) {
		SelectObject(capture->hdc, capture->old_bmp);
		DeleteDC(capture->hdc);
		DeleteObject(capture->bmp);
	}

	obs_enter_graphics();
	gs_texture_destroy(capture->texture);
	obs_leave_graphics();

	memset(capture, 0, sizeof(struct dc_capture));
}