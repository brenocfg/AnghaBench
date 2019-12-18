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
struct video_data {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct obs_core_video {int /*<<< orphan*/ ** mapped_surfaces; int /*<<< orphan*/ *** copy_surfaces; int /*<<< orphan*/ * textures_copied; } ;
typedef  int /*<<< orphan*/  gs_stagesurf_t ;

/* Variables and functions */
 int NUM_CHANNELS ; 
 int /*<<< orphan*/  gs_stagesurface_map (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool download_frame(struct obs_core_video *video,
				  int prev_texture, struct video_data *frame)
{
	if (!video->textures_copied[prev_texture])
		return false;

	for (int channel = 0; channel < NUM_CHANNELS; ++channel) {
		gs_stagesurf_t *surface =
			video->copy_surfaces[prev_texture][channel];
		if (surface) {
			if (!gs_stagesurface_map(surface, &frame->data[channel],
						 &frame->linesize[channel]))
				return false;

			video->mapped_surfaces[channel] = surface;
		}
	}
	return true;
}