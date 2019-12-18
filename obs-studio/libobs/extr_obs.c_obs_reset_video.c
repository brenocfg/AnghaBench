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
struct obs_video_info {int output_width; int output_height; int base_width; int base_height; int scale_type; int /*<<< orphan*/  output_format; int /*<<< orphan*/  fps_den; int /*<<< orphan*/  fps_num; int /*<<< orphan*/  range; int /*<<< orphan*/  colorspace; } ;
struct obs_core_video {int /*<<< orphan*/  graphics; scalar_t__ video; } ;
struct TYPE_2__ {struct obs_core_video video; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
#define  OBS_SCALE_AREA 133 
#define  OBS_SCALE_BICUBIC 132 
#define  OBS_SCALE_BILINEAR 131 
#define  OBS_SCALE_DISABLE 130 
#define  OBS_SCALE_LANCZOS 129 
#define  OBS_SCALE_POINT 128 
 int OBS_VIDEO_CURRENTLY_ACTIVE ; 
 int OBS_VIDEO_FAIL ; 
 int OBS_VIDEO_INVALID_PARAM ; 
 int OBS_VIDEO_SUCCESS ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 int format_is_yuv (int /*<<< orphan*/ ) ; 
 char* get_video_colorspace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_video_format_name (int /*<<< orphan*/ ) ; 
 char* get_video_range_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* obs ; 
 int /*<<< orphan*/  obs_free_graphics () ; 
 int /*<<< orphan*/  obs_free_video () ; 
 int obs_init_graphics (struct obs_video_info*) ; 
 int obs_init_video (struct obs_video_info*) ; 
 scalar_t__ obs_video_active () ; 
 int /*<<< orphan*/  size_valid (int,int) ; 
 int /*<<< orphan*/  stop_video () ; 

int obs_reset_video(struct obs_video_info *ovi)
{
	if (!obs)
		return OBS_VIDEO_FAIL;

	/* don't allow changing of video settings if active. */
	if (obs->video.video && obs_video_active())
		return OBS_VIDEO_CURRENTLY_ACTIVE;

	if (!size_valid(ovi->output_width, ovi->output_height) ||
	    !size_valid(ovi->base_width, ovi->base_height))
		return OBS_VIDEO_INVALID_PARAM;

	struct obs_core_video *video = &obs->video;

	stop_video();
	obs_free_video();

	/* align to multiple-of-two and SSE alignment sizes */
	ovi->output_width &= 0xFFFFFFFC;
	ovi->output_height &= 0xFFFFFFFE;

	if (!video->graphics) {
		int errorcode = obs_init_graphics(ovi);
		if (errorcode != OBS_VIDEO_SUCCESS) {
			obs_free_graphics();
			return errorcode;
		}
	}

	const char *scale_type_name = "";
	switch (ovi->scale_type) {
	case OBS_SCALE_DISABLE:
		scale_type_name = "Disabled";
		break;
	case OBS_SCALE_POINT:
		scale_type_name = "Point";
		break;
	case OBS_SCALE_BICUBIC:
		scale_type_name = "Bicubic";
		break;
	case OBS_SCALE_BILINEAR:
		scale_type_name = "Bilinear";
		break;
	case OBS_SCALE_LANCZOS:
		scale_type_name = "Lanczos";
		break;
	case OBS_SCALE_AREA:
		scale_type_name = "Area";
		break;
	}

	bool yuv = format_is_yuv(ovi->output_format);
	const char *yuv_format = get_video_colorspace_name(ovi->colorspace);
	const char *yuv_range =
		get_video_range_name(ovi->output_format, ovi->range);

	blog(LOG_INFO, "---------------------------------");
	blog(LOG_INFO,
	     "video settings reset:\n"
	     "\tbase resolution:   %dx%d\n"
	     "\toutput resolution: %dx%d\n"
	     "\tdownscale filter:  %s\n"
	     "\tfps:               %d/%d\n"
	     "\tformat:            %s\n"
	     "\tYUV mode:          %s%s%s",
	     ovi->base_width, ovi->base_height, ovi->output_width,
	     ovi->output_height, scale_type_name, ovi->fps_num, ovi->fps_den,
	     get_video_format_name(ovi->output_format),
	     yuv ? yuv_format : "None", yuv ? "/" : "", yuv ? yuv_range : "");

	return obs_init_video(ovi);
}