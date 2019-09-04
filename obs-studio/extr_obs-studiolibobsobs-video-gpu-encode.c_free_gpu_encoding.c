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
struct obs_tex_frame {int /*<<< orphan*/  tex_uv; int /*<<< orphan*/  tex; } ;
struct TYPE_3__ {scalar_t__ size; } ;
struct obs_core_video {TYPE_1__ gpu_encoder_avail_queue; TYPE_1__ gpu_encoder_queue; int /*<<< orphan*/ * gpu_encode_inactive; int /*<<< orphan*/ * gpu_encode_semaphore; } ;
typedef  int /*<<< orphan*/  frame ;

/* Variables and functions */
 int /*<<< orphan*/  circlebuf_free (TYPE_1__*) ; 
 int /*<<< orphan*/  circlebuf_pop_front (TYPE_1__*,struct obs_tex_frame*,int) ; 
 int /*<<< orphan*/  gs_texture_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_event_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_sem_destroy (int /*<<< orphan*/ *) ; 

void free_gpu_encoding(struct obs_core_video *video)
{
	if (video->gpu_encode_semaphore) {
		os_sem_destroy(video->gpu_encode_semaphore);
		video->gpu_encode_semaphore = NULL;
	}
	if (video->gpu_encode_inactive) {
		os_event_destroy(video->gpu_encode_inactive);
		video->gpu_encode_inactive = NULL;
	}

#define free_circlebuf(x) \
	do { \
		while (x.size) { \
			struct obs_tex_frame frame; \
			circlebuf_pop_front(&x, &frame, sizeof(frame)); \
			gs_texture_destroy(frame.tex); \
			gs_texture_destroy(frame.tex_uv); \
		} \
		circlebuf_free(&x); \
	} while (false)

	free_circlebuf(video->gpu_encoder_queue);
	free_circlebuf(video->gpu_encoder_avail_queue);
#undef free_circlebuf
}