#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct video_device {int /*<<< orphan*/ * ctrl_handler; int /*<<< orphan*/  name; int /*<<< orphan*/  entity; TYPE_1__* v4l2_dev; } ;
struct vb2_queue {int io_modes; int buf_struct_size; int min_buffers_needed; int /*<<< orphan*/  dev; int /*<<< orphan*/ * lock; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; struct capture_priv* drv_priv; void* type; } ;
struct v4l2_subdev_format {int /*<<< orphan*/  format; int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int /*<<< orphan*/  entity; TYPE_1__* v4l2_dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_7__ {TYPE_5__ pix; } ;
struct TYPE_8__ {TYPE_2__ fmt; void* type; } ;
struct imx_media_video_dev {TYPE_3__ fmt; int /*<<< orphan*/  cc; struct video_device* vfd; } ;
struct imx_media_buffer {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
struct capture_priv {int /*<<< orphan*/  ctrl_hdlr; int /*<<< orphan*/  src_sd_pad; TYPE_4__ vdev_pad; int /*<<< orphan*/  ready_q; int /*<<< orphan*/  dev; int /*<<< orphan*/  mutex; int /*<<< orphan*/  md; struct vb2_queue q; struct v4l2_subdev* src_sd; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SEL_ANY ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 void* V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  capture_qops ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_fmt ; 
 int /*<<< orphan*/  imx_media_find_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  imx_media_mbus_fmt_to_pix_fmt (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int media_create_pad_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int media_entity_pads_init (int /*<<< orphan*/ *,int,TYPE_4__*) ; 
 int /*<<< orphan*/  pad ; 
 struct capture_priv* to_capture_priv (struct imx_media_video_dev*) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/  vb2_dma_contig_memops ; 
 int vb2_queue_init (struct vb2_queue*) ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 

int imx_media_capture_device_register(struct imx_media_video_dev *vdev)
{
	struct capture_priv *priv = to_capture_priv(vdev);
	struct v4l2_subdev *sd = priv->src_sd;
	struct video_device *vfd = vdev->vfd;
	struct vb2_queue *vq = &priv->q;
	struct v4l2_subdev_format fmt_src;
	int ret;

	/* get media device */
	priv->md = dev_get_drvdata(sd->v4l2_dev->dev);

	vfd->v4l2_dev = sd->v4l2_dev;

	ret = video_register_device(vfd, VFL_TYPE_GRABBER, -1);
	if (ret) {
		v4l2_err(sd, "Failed to register video device\n");
		return ret;
	}

	vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vq->io_modes = VB2_MMAP | VB2_DMABUF;
	vq->drv_priv = priv;
	vq->buf_struct_size = sizeof(struct imx_media_buffer);
	vq->ops = &capture_qops;
	vq->mem_ops = &vb2_dma_contig_memops;
	vq->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	vq->lock = &priv->mutex;
	vq->min_buffers_needed = 2;
	vq->dev = priv->dev;

	ret = vb2_queue_init(vq);
	if (ret) {
		v4l2_err(sd, "vb2_queue_init failed\n");
		goto unreg;
	}

	INIT_LIST_HEAD(&priv->ready_q);

	priv->vdev_pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&vfd->entity, 1, &priv->vdev_pad);
	if (ret) {
		v4l2_err(sd, "failed to init dev pad\n");
		goto unreg;
	}

	/* create the link from the src_sd devnode pad to device node */
	ret = media_create_pad_link(&sd->entity, priv->src_sd_pad,
				    &vfd->entity, 0, 0);
	if (ret) {
		v4l2_err(sd, "failed to create link to device node\n");
		goto unreg;
	}

	/* setup default format */
	fmt_src.pad = priv->src_sd_pad;
	fmt_src.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	v4l2_subdev_call(sd, pad, get_fmt, NULL, &fmt_src);
	if (ret) {
		v4l2_err(sd, "failed to get src_sd format\n");
		goto unreg;
	}

	vdev->fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	imx_media_mbus_fmt_to_pix_fmt(&vdev->fmt.fmt.pix,
				      &fmt_src.format, NULL);
	vdev->cc = imx_media_find_format(vdev->fmt.fmt.pix.pixelformat,
					 CS_SEL_ANY, false);

	v4l2_info(sd, "Registered %s as /dev/%s\n", vfd->name,
		  video_device_node_name(vfd));

	vfd->ctrl_handler = &priv->ctrl_hdlr;

	return 0;
unreg:
	video_unregister_device(vfd);
	return ret;
}