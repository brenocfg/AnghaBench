#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct game_capture {TYPE_1__* global_hook_info; int /*<<< orphan*/  cursor_data; int /*<<< orphan*/  window; } ;
struct TYPE_5__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {scalar_t__ base_cy; scalar_t__ base_cx; scalar_t__ cy; scalar_t__ cx; scalar_t__ window; } ;
typedef  TYPE_2__ POINT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ClientToScreen (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  cursor_draw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,float,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void game_capture_render_cursor(struct game_capture *gc)
{
	POINT p = {0};
	HWND window;

	if (!gc->global_hook_info->base_cx || !gc->global_hook_info->base_cy)
		return;

	window = !!gc->global_hook_info->window
			 ? (HWND)(uintptr_t)gc->global_hook_info->window
			 : gc->window;

	ClientToScreen(window, &p);

	float x_scale = (float)gc->global_hook_info->cx /
			(float)gc->global_hook_info->base_cx;
	float y_scale = (float)gc->global_hook_info->cy /
			(float)gc->global_hook_info->base_cy;

	cursor_draw(&gc->cursor_data, -p.x, -p.y, x_scale, y_scale,
		    gc->global_hook_info->base_cx,
		    gc->global_hook_info->base_cy);
}