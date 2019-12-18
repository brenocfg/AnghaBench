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
struct video_scale_info {scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  range; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  format; } ;
struct video_output_info {int /*<<< orphan*/  format; } ;
struct obs_output {struct video_scale_info video_conversion; scalar_t__ scaled_height; scalar_t__ scaled_width; int /*<<< orphan*/  video; scalar_t__ video_conversion_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEO_CS_DEFAULT ; 
 int /*<<< orphan*/  VIDEO_RANGE_DEFAULT ; 
 scalar_t__ has_scaling (struct obs_output*) ; 
 scalar_t__ obs_output_get_height (struct obs_output*) ; 
 scalar_t__ obs_output_get_width (struct obs_output*) ; 
 struct video_output_info* video_output_get_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct video_scale_info *
get_video_conversion(struct obs_output *output)
{
	if (output->video_conversion_set) {
		if (!output->video_conversion.width)
			output->video_conversion.width =
				obs_output_get_width(output);

		if (!output->video_conversion.height)
			output->video_conversion.height =
				obs_output_get_height(output);

		return &output->video_conversion;

	} else if (has_scaling(output)) {
		const struct video_output_info *info =
			video_output_get_info(output->video);

		output->video_conversion.format = info->format;
		output->video_conversion.colorspace = VIDEO_CS_DEFAULT;
		output->video_conversion.range = VIDEO_RANGE_DEFAULT;
		output->video_conversion.width = output->scaled_width;
		output->video_conversion.height = output->scaled_height;
		return &output->video_conversion;
	}

	return NULL;
}