#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int force_shmem; scalar_t__ scale_cy; scalar_t__ scale_cx; int /*<<< orphan*/  force_scaling; int /*<<< orphan*/  capture_overlays; } ;
struct game_capture {TYPE_2__* global_hook_info; TYPE_1__ config; scalar_t__ process_is_64bit; int /*<<< orphan*/  global_hook_info_map; } ;
struct TYPE_4__ {int force_shmem; scalar_t__ cy; scalar_t__ cx; int /*<<< orphan*/  use_scale; int /*<<< orphan*/  capture_overlay; int /*<<< orphan*/  offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_MAP_ALL_ACCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 TYPE_2__* MapViewOfFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gs_shared_texture_available () ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 int /*<<< orphan*/  offsets32 ; 
 int /*<<< orphan*/  offsets64 ; 
 int /*<<< orphan*/  open_hook_info (struct game_capture*) ; 
 int /*<<< orphan*/  reset_frame_interval (struct game_capture*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static inline bool init_hook_info(struct game_capture *gc)
{
	gc->global_hook_info_map = open_hook_info(gc);
	if (!gc->global_hook_info_map) {
		warn("init_hook_info: get_hook_info failed: %lu",
		     GetLastError());
		return false;
	}

	gc->global_hook_info = MapViewOfFile(gc->global_hook_info_map,
					     FILE_MAP_ALL_ACCESS, 0, 0,
					     sizeof(*gc->global_hook_info));
	if (!gc->global_hook_info) {
		warn("init_hook_info: failed to map data view: %lu",
		     GetLastError());
		return false;
	}

	if (gc->config.force_shmem) {
		warn("init_hook_info: user is forcing shared memory "
		     "(multi-adapter compatibility mode)");
	}

	gc->global_hook_info->offsets = gc->process_is_64bit ? offsets64
							     : offsets32;
	gc->global_hook_info->capture_overlay = gc->config.capture_overlays;
	gc->global_hook_info->force_shmem = gc->config.force_shmem;
	gc->global_hook_info->use_scale = gc->config.force_scaling;
	if (gc->config.scale_cx)
		gc->global_hook_info->cx = gc->config.scale_cx;
	if (gc->config.scale_cy)
		gc->global_hook_info->cy = gc->config.scale_cy;
	reset_frame_interval(gc);

	obs_enter_graphics();
	if (!gs_shared_texture_available()) {
		warn("init_hook_info: shared texture capture unavailable");
		gc->global_hook_info->force_shmem = true;
	}
	obs_leave_graphics();

	return true;
}