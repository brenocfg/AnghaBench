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
struct video_output_info {int format; } ;
struct obs_video_info {int output_width; int output_height; } ;
struct obs_core_video {void*** copy_surfaces; int /*<<< orphan*/  video; } ;
struct TYPE_2__ {struct obs_core_video video; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_R8 ; 
 int /*<<< orphan*/  GS_R8G8 ; 
#define  VIDEO_FORMAT_I420 130 
#define  VIDEO_FORMAT_I444 129 
#define  VIDEO_FORMAT_NV12 128 
 void* gs_stagesurface_create (int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* obs ; 
 struct video_output_info* video_output_get_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool obs_init_gpu_copy_surfaces(struct obs_video_info *ovi, size_t i)
{
	struct obs_core_video *video = &obs->video;

	video->copy_surfaces[i][0] = gs_stagesurface_create(
		ovi->output_width, ovi->output_height, GS_R8);
	if (!video->copy_surfaces[i][0])
		return false;

	const struct video_output_info *info =
		video_output_get_info(video->video);
	switch (info->format) {
	case VIDEO_FORMAT_I420:
		video->copy_surfaces[i][1] = gs_stagesurface_create(
			ovi->output_width / 2, ovi->output_height / 2, GS_R8);
		if (!video->copy_surfaces[i][1])
			return false;
		video->copy_surfaces[i][2] = gs_stagesurface_create(
			ovi->output_width / 2, ovi->output_height / 2, GS_R8);
		if (!video->copy_surfaces[i][2])
			return false;
		break;
	case VIDEO_FORMAT_NV12:
		video->copy_surfaces[i][1] = gs_stagesurface_create(
			ovi->output_width / 2, ovi->output_height / 2, GS_R8G8);
		if (!video->copy_surfaces[i][1])
			return false;
		break;
	case VIDEO_FORMAT_I444:
		video->copy_surfaces[i][1] = gs_stagesurface_create(
			ovi->output_width, ovi->output_height, GS_R8);
		if (!video->copy_surfaces[i][1])
			return false;
		video->copy_surfaces[i][2] = gs_stagesurface_create(
			ovi->output_width, ovi->output_height, GS_R8);
		if (!video->copy_surfaces[i][2])
			return false;
		break;
	default:
		break;
	}

	return true;
}