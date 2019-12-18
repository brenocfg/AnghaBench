#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_5__ {int /*<<< orphan*/  array; } ;
struct TYPE_4__ {int /*<<< orphan*/  array; } ;
struct TYPE_6__ {int /*<<< orphan*/  array; } ;
struct game_capture {int wait_for_target_startup; TYPE_2__ executable; TYPE_1__ title; TYPE_3__ class; int /*<<< orphan*/  priority; } ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 scalar_t__ FindWindowW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INCLUDE_MINIMIZED ; 
 scalar_t__ dstr_cmpi (TYPE_3__*,char*) ; 
 scalar_t__ find_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_utf8_to_wcs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setup_window (struct game_capture*,scalar_t__) ; 

__attribute__((used)) static void get_selected_window(struct game_capture *gc)
{
	HWND window;

	if (dstr_cmpi(&gc->class, "dwm") == 0) {
		wchar_t class_w[512];
		os_utf8_to_wcs(gc->class.array, 0, class_w, 512);
		window = FindWindowW(class_w, NULL);
	} else {
		window = find_window(INCLUDE_MINIMIZED, gc->priority,
				     gc->class.array, gc->title.array,
				     gc->executable.array);
	}

	if (window) {
		setup_window(gc, window);
	} else {
		gc->wait_for_target_startup = true;
	}
}