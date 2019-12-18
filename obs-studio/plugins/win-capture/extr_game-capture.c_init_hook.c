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
struct game_capture {int active; scalar_t__ retrying; int /*<<< orphan*/ * next_window; int /*<<< orphan*/ * window; int /*<<< orphan*/  hook_init; TYPE_1__ config; } ;
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 scalar_t__ CAPTURE_MODE_ANY ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attempt_existing_hook (struct game_capture*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 scalar_t__ get_window_exe (struct dstr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_events (struct game_capture*) ; 
 int /*<<< orphan*/  init_hook_info (struct game_capture*) ; 
 int /*<<< orphan*/  init_keepalive (struct game_capture*) ; 
 int /*<<< orphan*/  init_pipe (struct game_capture*) ; 
 int /*<<< orphan*/  init_texture_mutexes (struct game_capture*) ; 
 int /*<<< orphan*/  inject_hook (struct game_capture*) ; 
 int is_blacklisted_exe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_target_process (struct game_capture*) ; 
 scalar_t__ target_suspended (struct game_capture*) ; 

__attribute__((used)) static bool init_hook(struct game_capture *gc)
{
	struct dstr exe = {0};
	bool blacklisted_process = false;

	if (gc->config.mode == CAPTURE_MODE_ANY) {
		if (get_window_exe(&exe, gc->next_window)) {
			info("attempting to hook fullscreen process: %s",
			     exe.array);
		}
	} else {
		if (get_window_exe(&exe, gc->next_window)) {
			info("attempting to hook process: %s", exe.array);
		}
	}

	blacklisted_process = is_blacklisted_exe(exe.array);
	if (blacklisted_process)
		info("cannot capture %s due to being blacklisted", exe.array);
	dstr_free(&exe);

	if (blacklisted_process) {
		return false;
	}
	if (target_suspended(gc)) {
		return false;
	}
	if (!open_target_process(gc)) {
		return false;
	}
	if (!init_keepalive(gc)) {
		return false;
	}
	if (!init_pipe(gc)) {
		return false;
	}
	if (!attempt_existing_hook(gc)) {
		if (!inject_hook(gc)) {
			return false;
		}
	}
	if (!init_texture_mutexes(gc)) {
		return false;
	}
	if (!init_hook_info(gc)) {
		return false;
	}
	if (!init_events(gc)) {
		return false;
	}

	SetEvent(gc->hook_init);

	gc->window = gc->next_window;
	gc->next_window = NULL;
	gc->active = true;
	gc->retrying = 0;
	return true;
}