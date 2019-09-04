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
struct v4l2_subdev_frame_interval_enum {int /*<<< orphan*/  interval; int /*<<< orphan*/  code; int /*<<< orphan*/  which; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pad; int /*<<< orphan*/  index; } ;
struct v4l2_frmivalenum {int /*<<< orphan*/  discrete; int /*<<< orphan*/  type; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  index; } ;
struct imx_media_pixfmt {int /*<<< orphan*/ * codes; } ;
struct file {int dummy; } ;
struct capture_priv {int /*<<< orphan*/  src_sd; int /*<<< orphan*/  src_sd_pad; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SEL_ANY ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMIVAL_TYPE_DISCRETE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  enum_frame_interval ; 
 struct imx_media_pixfmt* imx_media_find_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pad ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_frame_interval_enum*) ; 
 struct capture_priv* video_drvdata (struct file*) ; 

__attribute__((used)) static int capture_enum_frameintervals(struct file *file, void *fh,
				       struct v4l2_frmivalenum *fival)
{
	struct capture_priv *priv = video_drvdata(file);
	const struct imx_media_pixfmt *cc;
	struct v4l2_subdev_frame_interval_enum fie = {
		.index = fival->index,
		.pad = priv->src_sd_pad,
		.width = fival->width,
		.height = fival->height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	int ret;

	cc = imx_media_find_format(fival->pixel_format, CS_SEL_ANY, true);
	if (!cc)
		return -EINVAL;

	fie.code = cc->codes[0];

	ret = v4l2_subdev_call(priv->src_sd, pad, enum_frame_interval,
			       NULL, &fie);
	if (ret)
		return ret;

	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete = fie.interval;

	return 0;
}