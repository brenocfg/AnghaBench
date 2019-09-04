#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vpfe_video_device {int /*<<< orphan*/  pad; struct vpfe_device* vpfe_dev; } ;
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {TYPE_1__ format; int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; } ;
struct TYPE_6__ {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_5__ {TYPE_3__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct v4l2_fmtdesc {scalar_t__ index; int /*<<< orphan*/  pixelformat; } ;
struct media_pad {int /*<<< orphan*/  index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  get_fmt ; 
 int /*<<< orphan*/  mbus_to_pix (struct v4l2_mbus_framefmt*,TYPE_3__*) ; 
 struct media_pad* media_entity_remote_pad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 struct vpfe_video_device* video_drvdata (struct file*) ; 
 struct v4l2_subdev* vpfe_video_remote_subdev (struct vpfe_video_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vpfe_enum_fmt(struct file *file, void  *priv,
				   struct v4l2_fmtdesc *fmt)
{
	struct vpfe_video_device *video = video_drvdata(file);
	struct vpfe_device *vpfe_dev = video->vpfe_dev;
	struct v4l2_subdev_format sd_fmt;
	struct v4l2_mbus_framefmt mbus;
	struct v4l2_subdev *subdev;
	struct v4l2_format format;
	struct media_pad *remote;
	int ret;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_enum_fmt\n");

	/*
	 * since already subdev pad format is set,
	 * only one pixel format is available
	 */
	if (fmt->index > 0) {
		v4l2_err(&vpfe_dev->v4l2_dev, "Invalid index\n");
		return -EINVAL;
	}
	/* get the remote pad */
	remote = media_entity_remote_pad(&video->pad);
	if (!remote) {
		v4l2_err(&vpfe_dev->v4l2_dev,
			 "invalid remote pad for video node\n");
		return -EINVAL;
	}
	/* get the remote subdev */
	subdev = vpfe_video_remote_subdev(video, NULL);
	if (!subdev) {
		v4l2_err(&vpfe_dev->v4l2_dev,
			 "invalid remote subdev for video node\n");
		return -EINVAL;
	}
	sd_fmt.pad = remote->index;
	sd_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	/* get output format of remote subdev */
	ret = v4l2_subdev_call(subdev, pad, get_fmt, NULL, &sd_fmt);
	if (ret) {
		v4l2_err(&vpfe_dev->v4l2_dev,
			 "invalid remote subdev for video node\n");
		return ret;
	}
	/* convert to pix format */
	mbus.code = sd_fmt.format.code;
	mbus_to_pix(&mbus, &format.fmt.pix);
	/* copy the result */
	fmt->pixelformat = format.fmt.pix.pixelformat;

	return 0;
}