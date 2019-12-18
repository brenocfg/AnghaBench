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
struct game_capture {int /*<<< orphan*/ * data; TYPE_1__* global_hook_info; int /*<<< orphan*/  hook_data_map; int /*<<< orphan*/  pitch; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
typedef  enum capture_result { ____Placeholder_capture_result } capture_result ;
struct TYPE_2__ {int /*<<< orphan*/  map_size; int /*<<< orphan*/  map_id; int /*<<< orphan*/  pitch; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
typedef  int DWORD ;

/* Variables and functions */
 int CAPTURE_FAIL ; 
 int CAPTURE_RETRY ; 
 int CAPTURE_SUCCESS ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_MAP_ALL_ACCESS ; 
 int GetLastError () ; 
 int /*<<< orphan*/ * MapViewOfFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMEM_TEXTURE ; 
 int /*<<< orphan*/  UnmapViewOfFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_map_plus_id (struct game_capture*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static inline enum capture_result init_capture_data(struct game_capture *gc)
{
	gc->cx = gc->global_hook_info->cx;
	gc->cy = gc->global_hook_info->cy;
	gc->pitch = gc->global_hook_info->pitch;

	if (gc->data) {
		UnmapViewOfFile(gc->data);
		gc->data = NULL;
	}

	CloseHandle(gc->hook_data_map);

	gc->hook_data_map = open_map_plus_id(gc, SHMEM_TEXTURE,
					     gc->global_hook_info->map_id);
	if (!gc->hook_data_map) {
		DWORD error = GetLastError();
		if (error == 2) {
			return CAPTURE_RETRY;
		} else {
			warn("init_capture_data: failed to open file "
			     "mapping: %lu",
			     error);
		}
		return CAPTURE_FAIL;
	}

	gc->data = MapViewOfFile(gc->hook_data_map, FILE_MAP_ALL_ACCESS, 0, 0,
				 gc->global_hook_info->map_size);
	if (!gc->data) {
		warn("init_capture_data: failed to map data view: %lu",
		     GetLastError());
		return CAPTURE_FAIL;
	}

	return CAPTURE_SUCCESS;
}