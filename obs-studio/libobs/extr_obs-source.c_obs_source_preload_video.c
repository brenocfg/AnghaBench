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
struct obs_source_frame {int full_range; int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 scalar_t__ format_is_yuv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_preload_video_internal (int /*<<< orphan*/ *,struct obs_source_frame*) ; 

void obs_source_preload_video(obs_source_t *source,
			      const struct obs_source_frame *frame)
{
	if (!frame) {
		obs_source_preload_video_internal(source, NULL);
		return;
	}

	struct obs_source_frame new_frame = *frame;
	new_frame.full_range =
		format_is_yuv(frame->format) ? new_frame.full_range : true;

	obs_source_preload_video_internal(source, &new_frame);
}