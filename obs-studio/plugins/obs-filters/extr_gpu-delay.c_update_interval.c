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
typedef  int uint64_t ;
struct gpu_delay_filter_data {int interval_ns; int delay_ns; int /*<<< orphan*/  frames; int /*<<< orphan*/  target_valid; } ;
struct frame {int /*<<< orphan*/  render; } ;
typedef  int /*<<< orphan*/  frame ;

/* Variables and functions */
 int /*<<< orphan*/  GS_RGBA ; 
 int /*<<< orphan*/  GS_ZS_NONE ; 
 struct frame* circlebuf_data (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  circlebuf_pop_front (int /*<<< orphan*/ *,struct frame*,int) ; 
 int /*<<< orphan*/  circlebuf_upsize (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  free_textures (struct gpu_delay_filter_data*) ; 
 int /*<<< orphan*/  gs_texrender_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_texrender_destroy (int /*<<< orphan*/ ) ; 
 size_t num_frames (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 

__attribute__((used)) static void update_interval(struct gpu_delay_filter_data *f,
			    uint64_t new_interval_ns)
{
	if (!f->target_valid) {
		free_textures(f);
		return;
	}

	f->interval_ns = new_interval_ns;
	size_t num = (size_t)(f->delay_ns / new_interval_ns);

	if (num > num_frames(&f->frames)) {
		size_t prev_num = num_frames(&f->frames);

		obs_enter_graphics();

		circlebuf_upsize(&f->frames, num * sizeof(struct frame));

		for (size_t i = prev_num; i < num; i++) {
			struct frame *frame =
				circlebuf_data(&f->frames, i * sizeof(*frame));
			frame->render =
				gs_texrender_create(GS_RGBA, GS_ZS_NONE);
		}

		obs_leave_graphics();

	} else if (num < num_frames(&f->frames)) {
		obs_enter_graphics();

		while (num_frames(&f->frames) > num) {
			struct frame frame;
			circlebuf_pop_front(&f->frames, &frame, sizeof(frame));
			gs_texrender_destroy(frame.render);
		}

		obs_leave_graphics();
	}
}