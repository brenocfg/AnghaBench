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
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  left; int /*<<< orphan*/  top; } ;
struct v4l2_selection {TYPE_2__ r; int /*<<< orphan*/  target; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct bcm2835_codec_q_data {int /*<<< orphan*/  crop_height; int /*<<< orphan*/  crop_width; int /*<<< orphan*/  height; int /*<<< orphan*/  bytesperline; } ;
struct bcm2835_codec_ctx {TYPE_1__* dev; } ;
struct TYPE_3__ {int role; } ;

/* Variables and functions */
#define  DECODE 136 
 int EINVAL ; 
#define  ENCODE 135 
#define  ISP 134 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
#define  V4L2_SEL_TGT_COMPOSE 133 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 132 
#define  V4L2_SEL_TGT_COMPOSE_DEFAULT 131 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 struct bcm2835_codec_ctx* file2ctx (struct file*) ; 
 struct bcm2835_codec_q_data* get_q_data (struct bcm2835_codec_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_g_selection(struct file *file, void *priv,
			      struct v4l2_selection *s)
{
	struct bcm2835_codec_ctx *ctx = file2ctx(file);
	struct bcm2835_codec_q_data *q_data;
	bool capture_queue = s->type == V4L2_BUF_TYPE_VIDEO_CAPTURE ?
								true : false;

	if ((ctx->dev->role == DECODE && !capture_queue) ||
	    (ctx->dev->role == ENCODE && capture_queue))
		/* OUTPUT on decoder and CAPTURE on encoder are not valid. */
		return -EINVAL;

	q_data = get_q_data(ctx, s->type);
	if (!q_data)
		return -EINVAL;

	switch (ctx->dev->role) {
	case DECODE:
		switch (s->target) {
		case V4L2_SEL_TGT_COMPOSE_DEFAULT:
		case V4L2_SEL_TGT_COMPOSE:
			s->r.left = 0;
			s->r.top = 0;
			s->r.width = q_data->crop_width;
			s->r.height = q_data->crop_height;
			break;
		case V4L2_SEL_TGT_COMPOSE_BOUNDS:
			s->r.left = 0;
			s->r.top = 0;
			s->r.width = q_data->crop_width;
			s->r.height = q_data->crop_height;
			break;
		default:
			return -EINVAL;
		}
		break;
	case ENCODE:
		switch (s->target) {
		case V4L2_SEL_TGT_CROP_DEFAULT:
		case V4L2_SEL_TGT_CROP_BOUNDS:
			s->r.top = 0;
			s->r.left = 0;
			s->r.width = q_data->bytesperline;
			s->r.height = q_data->height;
			break;
		case V4L2_SEL_TGT_CROP:
			s->r.top = 0;
			s->r.left = 0;
			s->r.width = q_data->crop_width;
			s->r.height = q_data->crop_height;
			break;
		default:
			return -EINVAL;
		}
		break;
	case ISP:
		break;
	}

	return 0;
}