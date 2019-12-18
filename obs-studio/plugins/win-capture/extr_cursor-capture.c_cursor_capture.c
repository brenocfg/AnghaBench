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
struct cursor_data {int visible; scalar_t__ current_cursor; int /*<<< orphan*/  cursor_pos; } ;
typedef  int /*<<< orphan*/  ci ;
struct TYPE_3__ {int cbSize; scalar_t__ hCursor; int flags; int /*<<< orphan*/  ptScreenPos; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  HICON ;
typedef  TYPE_1__ CURSORINFO ;

/* Variables and functions */
 int CURSOR_SHOWING ; 
 int /*<<< orphan*/  CopyIcon (scalar_t__) ; 
 int /*<<< orphan*/  DestroyIcon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCursorInfo (TYPE_1__*) ; 
 int cursor_capture_icon (struct cursor_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void cursor_capture(struct cursor_data *data)
{
	CURSORINFO ci = {0};
	HICON icon;

	ci.cbSize = sizeof(ci);

	if (!GetCursorInfo(&ci)) {
		data->visible = false;
		return;
	}

	memcpy(&data->cursor_pos, &ci.ptScreenPos, sizeof(data->cursor_pos));

	if (data->current_cursor == ci.hCursor) {
		return;
	}

	icon = CopyIcon(ci.hCursor);
	data->visible = cursor_capture_icon(data, icon);
	data->current_cursor = ci.hCursor;
	if ((ci.flags & CURSOR_SHOWING) == 0)
		data->visible = false;
	DestroyIcon(icon);
}