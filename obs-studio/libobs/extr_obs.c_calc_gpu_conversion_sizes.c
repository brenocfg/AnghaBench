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
typedef  int /*<<< orphan*/  uint32_t ;
struct obs_video_info {scalar_t__ output_width; int /*<<< orphan*/  output_format; } ;
struct obs_core_video {int conversion_needed; char** conversion_techs; float conversion_width_i; } ;
struct TYPE_2__ {struct obs_core_video video; } ;

/* Variables and functions */
#define  VIDEO_FORMAT_I420 130 
#define  VIDEO_FORMAT_I444 129 
#define  VIDEO_FORMAT_NV12 128 
 TYPE_1__* obs ; 

__attribute__((used)) static inline void calc_gpu_conversion_sizes(const struct obs_video_info *ovi)
{
	struct obs_core_video *video = &obs->video;

	video->conversion_needed = false;
	video->conversion_techs[0] = NULL;
	video->conversion_techs[1] = NULL;
	video->conversion_techs[2] = NULL;
	video->conversion_width_i = 0.f;

	switch ((uint32_t)ovi->output_format) {
	case VIDEO_FORMAT_I420:
		video->conversion_needed = true;
		video->conversion_techs[0] = "Planar_Y";
		video->conversion_techs[1] = "Planar_U_Left";
		video->conversion_techs[2] = "Planar_V_Left";
		video->conversion_width_i = 1.f / (float)ovi->output_width;
		break;
	case VIDEO_FORMAT_NV12:
		video->conversion_needed = true;
		video->conversion_techs[0] = "NV12_Y";
		video->conversion_techs[1] = "NV12_UV";
		video->conversion_width_i = 1.f / (float)ovi->output_width;
		break;
	case VIDEO_FORMAT_I444:
		video->conversion_needed = true;
		video->conversion_techs[0] = "Planar_Y";
		video->conversion_techs[1] = "Planar_U";
		video->conversion_techs[2] = "Planar_V";
		break;
	}
}