#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int x; int y; } ;
struct TYPE_10__ {int flags; TYPE_1__ ptScreenPos; int /*<<< orphan*/  hCursor; } ;
struct dc_capture {TYPE_4__ ci; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_9__ {int /*<<< orphan*/  hbmMask; int /*<<< orphan*/  hbmColor; scalar_t__ yHotspot; scalar_t__ xHotspot; } ;
struct TYPE_8__ {int x; int y; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ POINT ;
typedef  TYPE_3__ ICONINFO ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HICON ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_4__ CURSORINFO ;

/* Variables and functions */
 int CURSOR_SHOWING ; 
 int /*<<< orphan*/  ClientToScreen (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  CopyIcon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DI_NORMAL ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyIcon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawIconEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetIconInfo (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void draw_cursor(struct dc_capture *capture, HDC hdc, HWND window)
{
	HICON icon;
	ICONINFO ii;
	CURSORINFO *ci = &capture->ci;
	POINT win_pos = {capture->x, capture->y};

	if (!(capture->ci.flags & CURSOR_SHOWING))
		return;

	icon = CopyIcon(capture->ci.hCursor);
	if (!icon)
		return;

	if (GetIconInfo(icon, &ii)) {
		POINT pos;

		if (window)
			ClientToScreen(window, &win_pos);

		pos.x = ci->ptScreenPos.x - (int)ii.xHotspot - win_pos.x;
		pos.y = ci->ptScreenPos.y - (int)ii.yHotspot - win_pos.y;

		DrawIconEx(hdc, pos.x, pos.y, icon, 0, 0, 0, NULL, DI_NORMAL);

		DeleteObject(ii.hbmColor);
		DeleteObject(ii.hbmMask);
	}

	DestroyIcon(icon);
}