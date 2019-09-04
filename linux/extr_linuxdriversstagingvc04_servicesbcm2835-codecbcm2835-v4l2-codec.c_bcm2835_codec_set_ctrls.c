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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_ctrl {int dummy; } ;
struct bcm2835_codec_ctx {int /*<<< orphan*/  hdl; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const V4L2_CID_MPEG_VIDEO_BITRATE_MODE ; 
 int /*<<< orphan*/  const V4L2_CID_MPEG_VIDEO_H264_I_PERIOD ; 
 int /*<<< orphan*/  const V4L2_CID_MPEG_VIDEO_H264_LEVEL ; 
 int /*<<< orphan*/  const V4L2_CID_MPEG_VIDEO_H264_PROFILE ; 
 int /*<<< orphan*/  const V4L2_CID_MPEG_VIDEO_REPEAT_SEQ_HEADER ; 
 int /*<<< orphan*/  bcm2835_codec_s_ctrl (struct v4l2_ctrl*) ; 
 struct v4l2_ctrl* v4l2_ctrl_find (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int bcm2835_codec_set_ctrls(struct bcm2835_codec_ctx *ctx)
{
	/*
	 * Query the control handler for the value of the various controls and
	 * set them.
	 */
	const u32 control_ids[] = {
		V4L2_CID_MPEG_VIDEO_BITRATE_MODE,
		V4L2_CID_MPEG_VIDEO_REPEAT_SEQ_HEADER,
		V4L2_CID_MPEG_VIDEO_H264_I_PERIOD,
		V4L2_CID_MPEG_VIDEO_H264_LEVEL,
		V4L2_CID_MPEG_VIDEO_H264_PROFILE,
	};
	int i;

	for (i = 0; i < ARRAY_SIZE(control_ids); i++) {
		struct v4l2_ctrl *ctrl;

		ctrl = v4l2_ctrl_find(&ctx->hdl, control_ids[i]);
		if (ctrl)
			bcm2835_codec_s_ctrl(ctrl);
	}

	return 0;
}