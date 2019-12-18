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
typedef  int /*<<< orphan*/  uint8_t ;
struct video_input {scalar_t__ cur_frame; scalar_t__ scaler; struct video_frame* frame; } ;
struct video_frame {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct video_data {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 size_t MAX_AV_PLANES ; 
 scalar_t__ MAX_CONVERT_BUFFERS ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int video_scaler_scale (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const* const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool scale_video_output(struct video_input *input,
				      struct video_data *data)
{
	bool success = true;

	if (input->scaler) {
		struct video_frame *frame;

		if (++input->cur_frame == MAX_CONVERT_BUFFERS)
			input->cur_frame = 0;

		frame = &input->frame[input->cur_frame];

		success = video_scaler_scale(input->scaler, frame->data,
					     frame->linesize,
					     (const uint8_t *const *)data->data,
					     data->linesize);

		if (success) {
			for (size_t i = 0; i < MAX_AV_PLANES; i++) {
				data->data[i] = frame->data[i];
				data->linesize[i] = frame->linesize[i];
			}
		} else {
			blog(LOG_WARNING, "video-io: Could not scale frame!");
		}
	}

	return success;
}