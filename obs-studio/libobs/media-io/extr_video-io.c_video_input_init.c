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
struct video_scale_info {scalar_t__ format; scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  range; } ;
struct TYPE_3__ {scalar_t__ width; scalar_t__ height; scalar_t__ format; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  range; } ;
struct video_output {TYPE_1__ info; } ;
struct TYPE_4__ {scalar_t__ width; scalar_t__ height; scalar_t__ format; } ;
struct video_input {TYPE_2__ conversion; int /*<<< orphan*/ * frame; int /*<<< orphan*/  scaler; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 size_t MAX_CONVERT_BUFFERS ; 
 int VIDEO_SCALER_BAD_CONVERSION ; 
 int VIDEO_SCALER_SUCCESS ; 
 int /*<<< orphan*/  VIDEO_SCALE_FAST_BILINEAR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  video_frame_init (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__) ; 
 int video_scaler_create (int /*<<< orphan*/ *,TYPE_2__*,struct video_scale_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool video_input_init(struct video_input *input,
				    struct video_output *video)
{
	if (input->conversion.width != video->info.width ||
	    input->conversion.height != video->info.height ||
	    input->conversion.format != video->info.format) {
		struct video_scale_info from = {.format = video->info.format,
						.width = video->info.width,
						.height = video->info.height,
						.range = video->info.range,
						.colorspace =
							video->info.colorspace};

		int ret = video_scaler_create(&input->scaler,
					      &input->conversion, &from,
					      VIDEO_SCALE_FAST_BILINEAR);
		if (ret != VIDEO_SCALER_SUCCESS) {
			if (ret == VIDEO_SCALER_BAD_CONVERSION)
				blog(LOG_ERROR, "video_input_init: Bad "
						"scale conversion type");
			else
				blog(LOG_ERROR, "video_input_init: Failed to "
						"create scaler");

			return false;
		}

		for (size_t i = 0; i < MAX_CONVERT_BUFFERS; i++)
			video_frame_init(&input->frame[i],
					 input->conversion.format,
					 input->conversion.width,
					 input->conversion.height);
	}

	return true;
}