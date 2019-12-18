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
struct game_capture {int active; int wait_for_target_startup; int capturing; scalar_t__ retrying; int /*<<< orphan*/ * copy_texture; int /*<<< orphan*/ * texture; scalar_t__* texture_mutexes; scalar_t__ target_process; scalar_t__ global_hook_info_map; scalar_t__ keepalive_mutex; scalar_t__ hook_data_map; scalar_t__ hook_init; scalar_t__ hook_exit; scalar_t__ hook_ready; scalar_t__ hook_stop; scalar_t__ hook_restart; int /*<<< orphan*/ * app_sid; int /*<<< orphan*/ * data; int /*<<< orphan*/ * global_hook_info; int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetEvent (scalar_t__) ; 
 int /*<<< orphan*/  UnmapViewOfFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_handle (scalar_t__*) ; 
 int /*<<< orphan*/  gs_texture_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  ipc_pipe_server_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 

__attribute__((used)) static void stop_capture(struct game_capture *gc)
{
	ipc_pipe_server_free(&gc->pipe);

	if (gc->hook_stop) {
		SetEvent(gc->hook_stop);
	}
	if (gc->global_hook_info) {
		UnmapViewOfFile(gc->global_hook_info);
		gc->global_hook_info = NULL;
	}
	if (gc->data) {
		UnmapViewOfFile(gc->data);
		gc->data = NULL;
	}

	if (gc->app_sid) {
		LocalFree(gc->app_sid);
		gc->app_sid = NULL;
	}

	close_handle(&gc->hook_restart);
	close_handle(&gc->hook_stop);
	close_handle(&gc->hook_ready);
	close_handle(&gc->hook_exit);
	close_handle(&gc->hook_init);
	close_handle(&gc->hook_data_map);
	close_handle(&gc->keepalive_mutex);
	close_handle(&gc->global_hook_info_map);
	close_handle(&gc->target_process);
	close_handle(&gc->texture_mutexes[0]);
	close_handle(&gc->texture_mutexes[1]);

	if (gc->texture) {
		obs_enter_graphics();
		gs_texture_destroy(gc->texture);
		obs_leave_graphics();
		gc->texture = NULL;
	}

	if (gc->active)
		info("capture stopped");

	gc->copy_texture = NULL;
	gc->wait_for_target_startup = false;
	gc->active = false;
	gc->capturing = false;

	if (gc->retrying)
		gc->retrying--;
}