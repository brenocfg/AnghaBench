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
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;
struct mmal_parameter_video_profile {int /*<<< orphan*/  level; int /*<<< orphan*/  profile; } ;
struct bcm2835_codec_ctx {TYPE_2__* component; TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  param ;
struct TYPE_4__ {int /*<<< orphan*/ * output; } ;
struct TYPE_3__ {int /*<<< orphan*/  instance; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAMETER_PROFILE ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_1 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_11 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_12 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_13 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_1b ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_2 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_21 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_22 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_3 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_31 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_32 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_4 ; 
 int /*<<< orphan*/  MMAL_VIDEO_PROFILE_H264_BASELINE ; 
 int /*<<< orphan*/  MMAL_VIDEO_PROFILE_H264_CONSTRAINED_BASELINE ; 
 int /*<<< orphan*/  MMAL_VIDEO_PROFILE_H264_HIGH ; 
 int /*<<< orphan*/  MMAL_VIDEO_PROFILE_H264_MAIN ; 
#define  V4L2_CID_MPEG_VIDEO_H264_LEVEL 145 
#define  V4L2_CID_MPEG_VIDEO_H264_PROFILE 144 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1B 143 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1_0 142 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1_1 141 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1_2 140 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1_3 139 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_2_0 138 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_2_1 137 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_2_2 136 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_3_0 135 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_3_1 134 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_3_2 133 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_4_0 132 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE 131 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_CONSTRAINED_BASELINE 130 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_HIGH 129 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_MAIN 128 
 int vchiq_mmal_port_parameter_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mmal_parameter_video_profile*,int*) ; 
 int vchiq_mmal_port_parameter_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mmal_parameter_video_profile*,int) ; 

__attribute__((used)) static int bcm2835_codec_set_level_profile(struct bcm2835_codec_ctx *ctx,
					   struct v4l2_ctrl *ctrl)
{
	struct mmal_parameter_video_profile param;
	int param_size = sizeof(param);
	int ret;

	/*
	 * Level and Profile are set via the same MMAL parameter.
	 * Retrieve the current settings and amend the one that has changed.
	 */
	ret = vchiq_mmal_port_parameter_get(ctx->dev->instance,
					    &ctx->component->output[0],
					    MMAL_PARAMETER_PROFILE,
					    &param,
					    &param_size);
	if (ret)
		return ret;

	switch (ctrl->id) {
	case V4L2_CID_MPEG_VIDEO_H264_PROFILE:
		switch (ctrl->val) {
		case V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE:
			param.profile = MMAL_VIDEO_PROFILE_H264_BASELINE;
			break;
		case V4L2_MPEG_VIDEO_H264_PROFILE_CONSTRAINED_BASELINE:
			param.profile =
				MMAL_VIDEO_PROFILE_H264_CONSTRAINED_BASELINE;
			break;
		case V4L2_MPEG_VIDEO_H264_PROFILE_MAIN:
			param.profile = MMAL_VIDEO_PROFILE_H264_MAIN;
			break;
		case V4L2_MPEG_VIDEO_H264_PROFILE_HIGH:
			param.profile = MMAL_VIDEO_PROFILE_H264_HIGH;
			break;
		default:
			/* Should never get here */
			break;
		}
		break;

	case V4L2_CID_MPEG_VIDEO_H264_LEVEL:
		switch (ctrl->val) {
		case V4L2_MPEG_VIDEO_H264_LEVEL_1_0:
			param.level = MMAL_VIDEO_LEVEL_H264_1;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_1B:
			param.level = MMAL_VIDEO_LEVEL_H264_1b;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_1_1:
			param.level = MMAL_VIDEO_LEVEL_H264_11;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_1_2:
			param.level = MMAL_VIDEO_LEVEL_H264_12;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_1_3:
			param.level = MMAL_VIDEO_LEVEL_H264_13;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_2_0:
			param.level = MMAL_VIDEO_LEVEL_H264_2;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_2_1:
			param.level = MMAL_VIDEO_LEVEL_H264_21;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_2_2:
			param.level = MMAL_VIDEO_LEVEL_H264_22;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_3_0:
			param.level = MMAL_VIDEO_LEVEL_H264_3;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_3_1:
			param.level = MMAL_VIDEO_LEVEL_H264_31;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_3_2:
			param.level = MMAL_VIDEO_LEVEL_H264_32;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_4_0:
			param.level = MMAL_VIDEO_LEVEL_H264_4;
			break;
		default:
			/* Should never get here */
			break;
		}
	}
	ret = vchiq_mmal_port_parameter_set(ctx->dev->instance,
					    &ctx->component->output[0],
					    MMAL_PARAMETER_PROFILE,
					    &param,
					    param_size);

	return ret;
}