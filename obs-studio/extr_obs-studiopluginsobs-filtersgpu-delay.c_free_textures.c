#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ size; } ;
struct gpu_delay_filter_data {TYPE_1__ frames; } ;
struct frame {int /*<<< orphan*/  render; } ;
typedef  int /*<<< orphan*/  frame ;

/* Variables and functions */
 int /*<<< orphan*/  circlebuf_free (TYPE_1__*) ; 
 int /*<<< orphan*/  circlebuf_pop_front (TYPE_1__*,struct frame*,int) ; 
 int /*<<< orphan*/  gs_texrender_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 

__attribute__((used)) static void free_textures(struct gpu_delay_filter_data *f)
{
	obs_enter_graphics();
	while (f->frames.size) {
		struct frame frame;
		circlebuf_pop_front(&f->frames, &frame, sizeof(frame));
		gs_texrender_destroy(frame.render);
	}
	circlebuf_free(&f->frames);
	obs_leave_graphics();
}