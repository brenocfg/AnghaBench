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
struct TYPE_2__ {scalar_t__ mode; } ;
struct game_capture {scalar_t__ process_id; int error_acquiring; int active; int /*<<< orphan*/  thread_id; scalar_t__ next_window; TYPE_1__ config; } ;

/* Variables and functions */
 scalar_t__ CAPTURE_MODE_ANY ; 
 scalar_t__ GetCurrentProcessId () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetWindowThreadProcessId (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  get_fullscreen_window (struct game_capture*) ; 
 int /*<<< orphan*/  get_selected_window (struct game_capture*) ; 
 int /*<<< orphan*/  init_hook (struct game_capture*) ; 
 int /*<<< orphan*/  stop_capture (struct game_capture*) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void try_hook(struct game_capture *gc)
{
	if (gc->config.mode == CAPTURE_MODE_ANY) {
		get_fullscreen_window(gc);
	} else {
		get_selected_window(gc);
	}

	if (gc->next_window) {
		gc->thread_id = GetWindowThreadProcessId(gc->next_window,
							 &gc->process_id);

		// Make sure we never try to hook ourselves (projector)
		if (gc->process_id == GetCurrentProcessId())
			return;

		if (!gc->thread_id && gc->process_id)
			return;
		if (!gc->process_id) {
			warn("error acquiring, failed to get window "
			     "thread/process ids: %lu",
			     GetLastError());
			gc->error_acquiring = true;
			return;
		}

		if (!init_hook(gc)) {
			stop_capture(gc);
		}
	} else {
		gc->active = false;
	}
}