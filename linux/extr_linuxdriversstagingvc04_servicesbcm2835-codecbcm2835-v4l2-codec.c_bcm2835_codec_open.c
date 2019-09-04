#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl_handler {int error; } ;
struct file {TYPE_2__* private_data; } ;
struct bcm2835_codec_dev {scalar_t__ role; int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/  num_inst; int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  m2m_ctx; struct v4l2_ctrl_handler* ctrl_handler; } ;
struct bcm2835_codec_ctx {int bitrate; TYPE_2__ fh; struct v4l2_ctrl_handler hdl; struct bcm2835_codec_dev* dev; int /*<<< orphan*/  colorspace; TYPE_1__* q_data; } ;
struct TYPE_4__ {void* fmt; void* height; void* crop_width; void* bytesperline; void* sizeimage; void* crop_height; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 void* DEFAULT_HEIGHT ; 
 void* DEFAULT_WIDTH ; 
 scalar_t__ ENCODE ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_BITRATE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_BITRATE_MODE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_I_PERIOD ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_PROFILE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_REPEAT_SEQ_HEADER ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_REC709 ; 
 size_t V4L2_M2M_DST ; 
 size_t V4L2_M2M_SRC ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_BITRATE_MODE_CBR ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_BITRATE_MODE_VBR ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_LEVEL_1B ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_LEVEL_1_0 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_LEVEL_1_1 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_LEVEL_1_2 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_LEVEL_1_3 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_LEVEL_2_0 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_LEVEL_2_1 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_LEVEL_2_2 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_LEVEL_3_0 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_LEVEL_3_1 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_LEVEL_3_2 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_LEVEL_4_0 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_LEVEL_4_1 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_LEVEL_4_2 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_PROFILE_CONSTRAINED_BASELINE ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_PROFILE_HIGH ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_H264_PROFILE_MAIN ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcm2835_codec_ctrl_ops ; 
 void* get_bytesperline (void*,void*) ; 
 void* get_default_format (struct bcm2835_codec_dev*,int) ; 
 void* get_sizeimage (void*,void*,void*,void*) ; 
 int /*<<< orphan*/  kfree (struct bcm2835_codec_ctx*) ; 
 struct bcm2835_codec_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_init ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_fh_add (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_fh_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_init (int /*<<< orphan*/ ,struct bcm2835_codec_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_set_dst_buffered (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_m2m_set_src_buffered (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct bcm2835_codec_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int bcm2835_codec_open(struct file *file)
{
	struct bcm2835_codec_dev *dev = video_drvdata(file);
	struct bcm2835_codec_ctx *ctx = NULL;
	struct v4l2_ctrl_handler *hdl;
	int rc = 0;

	if (mutex_lock_interruptible(&dev->dev_mutex)) {
		v4l2_err(&dev->v4l2_dev, "Mutex fail\n");
		return -ERESTARTSYS;
	}
	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		rc = -ENOMEM;
		goto open_unlock;
	}

	ctx->q_data[V4L2_M2M_SRC].fmt = get_default_format(dev, false);
	ctx->q_data[V4L2_M2M_DST].fmt = get_default_format(dev, true);

	ctx->q_data[V4L2_M2M_SRC].crop_width = DEFAULT_WIDTH;
	ctx->q_data[V4L2_M2M_SRC].crop_height = DEFAULT_HEIGHT;
	ctx->q_data[V4L2_M2M_SRC].height = DEFAULT_HEIGHT;
	ctx->q_data[V4L2_M2M_SRC].bytesperline =
			get_bytesperline(DEFAULT_WIDTH,
					 ctx->q_data[V4L2_M2M_SRC].fmt);
	ctx->q_data[V4L2_M2M_SRC].sizeimage =
		get_sizeimage(ctx->q_data[V4L2_M2M_SRC].bytesperline,
			      ctx->q_data[V4L2_M2M_SRC].crop_width,
			      ctx->q_data[V4L2_M2M_SRC].height,
			      ctx->q_data[V4L2_M2M_SRC].fmt);

	ctx->q_data[V4L2_M2M_DST].crop_width = DEFAULT_WIDTH;
	ctx->q_data[V4L2_M2M_DST].crop_height = DEFAULT_HEIGHT;
	ctx->q_data[V4L2_M2M_DST].height = DEFAULT_HEIGHT;
	ctx->q_data[V4L2_M2M_DST].bytesperline =
			get_bytesperline(DEFAULT_WIDTH,
					 ctx->q_data[V4L2_M2M_DST].fmt);
	ctx->q_data[V4L2_M2M_DST].sizeimage =
		get_sizeimage(ctx->q_data[V4L2_M2M_DST].bytesperline,
			      ctx->q_data[V4L2_M2M_DST].crop_width,
			      ctx->q_data[V4L2_M2M_DST].height,
			      ctx->q_data[V4L2_M2M_DST].fmt);

	ctx->colorspace = V4L2_COLORSPACE_REC709;
	ctx->bitrate = 10 * 1000 * 1000;

	/* Initialise V4L2 contexts */
	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->private_data = &ctx->fh;
	ctx->dev = dev;
	hdl = &ctx->hdl;
	if (dev->role == ENCODE) {
		/* Encode controls */
		v4l2_ctrl_handler_init(hdl, 6);

		v4l2_ctrl_new_std_menu(hdl, &bcm2835_codec_ctrl_ops,
				       V4L2_CID_MPEG_VIDEO_BITRATE_MODE,
				       V4L2_MPEG_VIDEO_BITRATE_MODE_CBR, 0,
				       V4L2_MPEG_VIDEO_BITRATE_MODE_VBR);
		v4l2_ctrl_new_std(hdl, &bcm2835_codec_ctrl_ops,
				  V4L2_CID_MPEG_VIDEO_BITRATE,
				  25 * 1000, 25 * 1000 * 1000,
				  25 * 1000, 10 * 1000 * 1000);
		v4l2_ctrl_new_std(hdl, &bcm2835_codec_ctrl_ops,
				  V4L2_CID_MPEG_VIDEO_REPEAT_SEQ_HEADER,
				  0, 1,
				  1, 0);
		v4l2_ctrl_new_std(hdl, &bcm2835_codec_ctrl_ops,
				  V4L2_CID_MPEG_VIDEO_H264_I_PERIOD,
				  0, 0x7FFFFFFF,
				  1, 60);
		v4l2_ctrl_new_std_menu(hdl, &bcm2835_codec_ctrl_ops,
				       V4L2_CID_MPEG_VIDEO_H264_LEVEL,
				       V4L2_MPEG_VIDEO_H264_LEVEL_4_2,
				       ~(BIT(V4L2_MPEG_VIDEO_H264_LEVEL_1_0) |
					 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_1B) |
					 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_1_1) |
					 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_1_2) |
					 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_1_3) |
					 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_2_0) |
					 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_2_1) |
					 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_2_2) |
					 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_3_0) |
					 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_3_1) |
					 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_3_2) |
					 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_4_0) |
					 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_4_1) |
					 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_4_2)),
				       V4L2_MPEG_VIDEO_H264_LEVEL_4_0);
		v4l2_ctrl_new_std_menu(hdl, &bcm2835_codec_ctrl_ops,
				       V4L2_CID_MPEG_VIDEO_H264_PROFILE,
				       V4L2_MPEG_VIDEO_H264_PROFILE_HIGH,
				       ~(BIT(V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE) |
					 BIT(V4L2_MPEG_VIDEO_H264_PROFILE_CONSTRAINED_BASELINE) |
					 BIT(V4L2_MPEG_VIDEO_H264_PROFILE_MAIN) |
					 BIT(V4L2_MPEG_VIDEO_H264_PROFILE_HIGH)),
					V4L2_MPEG_VIDEO_H264_PROFILE_HIGH);
		if (hdl->error) {
			rc = hdl->error;
			goto free_ctrl_handler;
		}
		ctx->fh.ctrl_handler = hdl;
		v4l2_ctrl_handler_setup(hdl);
	}

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->m2m_dev, ctx, &queue_init);

	if (IS_ERR(ctx->fh.m2m_ctx)) {
		rc = PTR_ERR(ctx->fh.m2m_ctx);

		goto free_ctrl_handler;
	}

	/* Set both queues as buffered as we have buffering in the VPU. That
	 * means that we will be scheduled whenever either an input or output
	 * buffer is available (otherwise one of each are required).
	 */
	v4l2_m2m_set_src_buffered(ctx->fh.m2m_ctx, true);
	v4l2_m2m_set_dst_buffered(ctx->fh.m2m_ctx, true);

	v4l2_fh_add(&ctx->fh);
	atomic_inc(&dev->num_inst);

	mutex_unlock(&dev->dev_mutex);
	return 0;

free_ctrl_handler:
	v4l2_ctrl_handler_free(hdl);
	kfree(ctx);
open_unlock:
	mutex_unlock(&dev->dev_mutex);
	return rc;
}