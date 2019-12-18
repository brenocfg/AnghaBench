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
struct TYPE_2__ {int /*<<< orphan*/  hook_rate; } ;
struct game_capture {int wait_for_target_startup; float retry_interval; int /*<<< orphan*/  next_window; TYPE_1__ config; int /*<<< orphan*/  app_sid; int /*<<< orphan*/  is_app; scalar_t__ process_id; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  EVENT_CAPTURE_RESTART ; 
 int /*<<< orphan*/  GetWindowThreadProcessId (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  PROCESS_QUERY_INFORMATION ; 
 int /*<<< orphan*/  get_app_sid (scalar_t__) ; 
 float hook_rate_to_float (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_app (scalar_t__) ; 
 scalar_t__ open_event_gc (struct game_capture*,int /*<<< orphan*/ ) ; 
 scalar_t__ open_process (int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static void setup_window(struct game_capture *gc, HWND window)
{
	HANDLE hook_restart;
	HANDLE process;

	GetWindowThreadProcessId(window, &gc->process_id);
	if (gc->process_id) {
		process = open_process(PROCESS_QUERY_INFORMATION, false,
				       gc->process_id);
		if (process) {
			gc->is_app = is_app(process);
			if (gc->is_app) {
				gc->app_sid = get_app_sid(process);
			}
			CloseHandle(process);
		}
	}

	/* do not wait if we're re-hooking a process */
	hook_restart = open_event_gc(gc, EVENT_CAPTURE_RESTART);
	if (hook_restart) {
		gc->wait_for_target_startup = false;
		CloseHandle(hook_restart);
	}

	/* otherwise if it's an unhooked process, always wait a bit for the
	 * target process to start up before starting the hook process;
	 * sometimes they have important modules to load first or other hooks
	 * (such as steam) need a little bit of time to load.  ultimately this
	 * helps prevent crashes */
	if (gc->wait_for_target_startup) {
		gc->retry_interval =
			3.0f * hook_rate_to_float(gc->config.hook_rate);
		gc->wait_for_target_startup = false;
	} else {
		gc->next_window = window;
	}
}