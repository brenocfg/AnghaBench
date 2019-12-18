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
struct TYPE_2__ {scalar_t__ mode; scalar_t__ cursor; int /*<<< orphan*/  hook_rate; } ;
struct game_capture {float retry_time; int activate_hook; int showing; int error_acquiring; float retry_interval; float fps_reset_time; int /*<<< orphan*/  cursor_data; TYPE_1__ config; int /*<<< orphan*/  (* copy_texture ) (struct game_capture*) ;scalar_t__ active; scalar_t__ capturing; scalar_t__ hook_ready; scalar_t__ injector_process; scalar_t__ process_id; scalar_t__ hook_stop; int /*<<< orphan*/  source; int /*<<< orphan*/  priority; int /*<<< orphan*/  class; int /*<<< orphan*/  title; int /*<<< orphan*/  executable; int /*<<< orphan*/  hotkey_window; int /*<<< orphan*/  activate_hook_now; int /*<<< orphan*/  deactivate_hook; } ;
typedef  enum capture_result { ____Placeholder_capture_result } capture_result ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ CAPTURE_MODE_ANY ; 
 int CAPTURE_RETRY ; 
 int CAPTURE_SUCCESS ; 
 float ERROR_RETRY_INTERVAL ; 
 int /*<<< orphan*/  EVENT_HOOK_READY ; 
 int /*<<< orphan*/  GetExitCodeProcess (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  WINDOW_PRIORITY_CLASS ; 
 int /*<<< orphan*/  capture_valid (struct game_capture*) ; 
 int /*<<< orphan*/  check_foreground_window (struct game_capture*,float) ; 
 int /*<<< orphan*/  close_handle (scalar_t__*) ; 
 int /*<<< orphan*/  cursor_capture (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  get_uwp_actual_window (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_window_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ get_window_exe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_window_title (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 float hook_rate_to_float (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info (char*) ; 
 int init_capture_data (struct game_capture*) ; 
 scalar_t__ is_uwp_window (int /*<<< orphan*/ ) ; 
 scalar_t__ object_signalled (scalar_t__) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 int /*<<< orphan*/  obs_source_showing (int /*<<< orphan*/ ) ; 
 scalar_t__ open_event_gc (struct game_capture*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_atomic_load_long (int /*<<< orphan*/ *) ; 
 int os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reset_frame_interval (struct game_capture*) ; 
 scalar_t__ start_capture (struct game_capture*) ; 
 int /*<<< orphan*/  stop_capture (struct game_capture*) ; 
 int /*<<< orphan*/  stub1 (struct game_capture*) ; 
 int /*<<< orphan*/  try_hook (struct game_capture*) ; 
 int /*<<< orphan*/  warn (char*,long) ; 

__attribute__((used)) static void game_capture_tick(void *data, float seconds)
{
	struct game_capture *gc = data;
	bool deactivate = os_atomic_set_bool(&gc->deactivate_hook, false);
	bool activate_now = os_atomic_set_bool(&gc->activate_hook_now, false);

	if (activate_now) {
		HWND hwnd = (HWND)(uintptr_t)os_atomic_load_long(
			&gc->hotkey_window);

		if (is_uwp_window(hwnd))
			hwnd = get_uwp_actual_window(hwnd);

		if (get_window_exe(&gc->executable, hwnd)) {
			get_window_title(&gc->title, hwnd);
			get_window_class(&gc->class, hwnd);

			gc->priority = WINDOW_PRIORITY_CLASS;
			gc->retry_time = 10.0f * hook_rate_to_float(
							 gc->config.hook_rate);
			gc->activate_hook = true;
		} else {
			deactivate = false;
			activate_now = false;
		}
	} else if (deactivate) {
		gc->activate_hook = false;
	}

	if (!obs_source_showing(gc->source)) {
		if (gc->showing) {
			if (gc->active)
				stop_capture(gc);
			gc->showing = false;
		}
		return;

	} else if (!gc->showing) {
		gc->retry_time =
			10.0f * hook_rate_to_float(gc->config.hook_rate);
	}

	if (gc->hook_stop && object_signalled(gc->hook_stop)) {
		debug("hook stop signal received");
		stop_capture(gc);
	}
	if (gc->active && deactivate) {
		stop_capture(gc);
	}

	if (gc->active && !gc->hook_ready && gc->process_id) {
		gc->hook_ready = open_event_gc(gc, EVENT_HOOK_READY);
	}

	if (gc->injector_process && object_signalled(gc->injector_process)) {
		DWORD exit_code = 0;

		GetExitCodeProcess(gc->injector_process, &exit_code);
		close_handle(&gc->injector_process);

		if (exit_code != 0) {
			warn("inject process failed: %ld", (long)exit_code);
			gc->error_acquiring = true;

		} else if (!gc->capturing) {
			gc->retry_interval =
				ERROR_RETRY_INTERVAL *
				hook_rate_to_float(gc->config.hook_rate);
			stop_capture(gc);
		}
	}

	if (gc->hook_ready && object_signalled(gc->hook_ready)) {
		debug("capture initializing!");
		enum capture_result result = init_capture_data(gc);

		if (result == CAPTURE_SUCCESS)
			gc->capturing = start_capture(gc);
		else
			debug("init_capture_data failed");

		if (result != CAPTURE_RETRY && !gc->capturing) {
			gc->retry_interval =
				ERROR_RETRY_INTERVAL *
				hook_rate_to_float(gc->config.hook_rate);
			stop_capture(gc);
		}
	}

	gc->retry_time += seconds;

	if (!gc->active) {
		if (!gc->error_acquiring &&
		    gc->retry_time > gc->retry_interval) {
			if (gc->config.mode == CAPTURE_MODE_ANY ||
			    gc->activate_hook) {
				try_hook(gc);
				gc->retry_time = 0.0f;
			}
		}
	} else {
		if (!capture_valid(gc)) {
			info("capture window no longer exists, "
			     "terminating capture");
			stop_capture(gc);
		} else {
			if (gc->copy_texture) {
				obs_enter_graphics();
				gc->copy_texture(gc);
				obs_leave_graphics();
			}

			if (gc->config.cursor) {
				check_foreground_window(gc, seconds);
				obs_enter_graphics();
				cursor_capture(&gc->cursor_data);
				obs_leave_graphics();
			}

			gc->fps_reset_time += seconds;
			if (gc->fps_reset_time >= gc->retry_interval) {
				reset_frame_interval(gc);
				gc->fps_reset_time = 0.0f;
			}
		}
	}

	if (!gc->showing)
		gc->showing = true;
}