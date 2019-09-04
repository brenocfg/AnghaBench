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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct v4l2_subdev_format {size_t pad; int /*<<< orphan*/  which; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_pix_format {int dummy; } ;
struct prp_priv {scalar_t__ stream_count; int /*<<< orphan*/  lock; struct imx_media_pixfmt const** cc; int /*<<< orphan*/ * format_mbus; struct imx_media_video_dev* vdev; } ;
struct imx_media_video_dev {int dummy; } ;
struct imx_media_pixfmt {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 size_t PRPENCVF_NUM_PADS ; 
 size_t PRPENCVF_SINK_PAD ; 
 size_t PRPENCVF_SRC_PAD ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_TRY ; 
 struct v4l2_mbus_framefmt* __prp_get_fmt (struct prp_priv*,struct v4l2_subdev_pad_config*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_capture_device_set_format (struct imx_media_video_dev*,struct v4l2_pix_format*) ; 
 int /*<<< orphan*/  imx_media_mbus_fmt_to_pix_fmt (struct v4l2_pix_format*,int /*<<< orphan*/ *,struct imx_media_pixfmt const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prp_try_fmt (struct prp_priv*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*,struct imx_media_pixfmt const**) ; 
 struct prp_priv* sd_to_priv (struct v4l2_subdev*) ; 

__attribute__((used)) static int prp_set_fmt(struct v4l2_subdev *sd,
		       struct v4l2_subdev_pad_config *cfg,
		       struct v4l2_subdev_format *sdformat)
{
	struct prp_priv *priv = sd_to_priv(sd);
	struct imx_media_video_dev *vdev = priv->vdev;
	const struct imx_media_pixfmt *cc;
	struct v4l2_pix_format vdev_fmt;
	struct v4l2_mbus_framefmt *fmt;
	int ret = 0;

	if (sdformat->pad >= PRPENCVF_NUM_PADS)
		return -EINVAL;

	mutex_lock(&priv->lock);

	if (priv->stream_count > 0) {
		ret = -EBUSY;
		goto out;
	}

	prp_try_fmt(priv, cfg, sdformat, &cc);

	fmt = __prp_get_fmt(priv, cfg, sdformat->pad, sdformat->which);
	*fmt = sdformat->format;

	/* propagate a default format to source pad */
	if (sdformat->pad == PRPENCVF_SINK_PAD) {
		const struct imx_media_pixfmt *outcc;
		struct v4l2_mbus_framefmt *outfmt;
		struct v4l2_subdev_format format;

		format.pad = PRPENCVF_SRC_PAD;
		format.which = sdformat->which;
		format.format = sdformat->format;
		prp_try_fmt(priv, cfg, &format, &outcc);

		outfmt = __prp_get_fmt(priv, cfg, PRPENCVF_SRC_PAD,
				       sdformat->which);
		*outfmt = format.format;
		if (sdformat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
			priv->cc[PRPENCVF_SRC_PAD] = outcc;
	}

	if (sdformat->which == V4L2_SUBDEV_FORMAT_TRY)
		goto out;

	priv->cc[sdformat->pad] = cc;

	/* propagate output pad format to capture device */
	imx_media_mbus_fmt_to_pix_fmt(&vdev_fmt,
				      &priv->format_mbus[PRPENCVF_SRC_PAD],
				      priv->cc[PRPENCVF_SRC_PAD]);
	mutex_unlock(&priv->lock);
	imx_media_capture_device_set_format(vdev, &vdev_fmt);

	return 0;
out:
	mutex_unlock(&priv->lock);
	return ret;
}