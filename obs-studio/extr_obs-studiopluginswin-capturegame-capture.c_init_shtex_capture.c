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
struct game_capture {int /*<<< orphan*/  texture; TYPE_1__* shtex_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tex_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  gs_texture_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_texture_open_shared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static inline bool init_shtex_capture(struct game_capture *gc)
{
	obs_enter_graphics();
	gs_texture_destroy(gc->texture);
	gc->texture = gs_texture_open_shared(gc->shtex_data->tex_handle);
	obs_leave_graphics();

	if (!gc->texture) {
		warn("init_shtex_capture: failed to open shared handle");
		return false;
	}

	return true;
}