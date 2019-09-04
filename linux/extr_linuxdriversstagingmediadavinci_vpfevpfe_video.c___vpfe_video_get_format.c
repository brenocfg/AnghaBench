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
typedef  int /*<<< orphan*/  u32 ;
struct vpfe_video_device {int /*<<< orphan*/  type; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev_format {int /*<<< orphan*/  format; int /*<<< orphan*/  pad; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {TYPE_1__ fmt; int /*<<< orphan*/  type; } ;
struct media_pad {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  get_fmt ; 
 int /*<<< orphan*/  mbus_to_pix (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct media_pad* media_entity_remote_pad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fill_pix_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 struct v4l2_subdev* vpfe_video_remote_subdev (struct vpfe_video_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
__vpfe_video_get_format(struct vpfe_video_device *video,
			struct v4l2_format *format)
{
	struct v4l2_subdev_format fmt;
	struct v4l2_subdev *subdev;
	struct media_pad *remote;
	u32 pad;
	int ret;

	subdev = vpfe_video_remote_subdev(video, &pad);
	if (!subdev)
		return -EINVAL;

	fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	remote = media_entity_remote_pad(&video->pad);
	fmt.pad = remote->index;

	ret = v4l2_subdev_call(subdev, pad, get_fmt, NULL, &fmt);
	if (ret == -ENOIOCTLCMD)
		return -EINVAL;

	format->type = video->type;
	/* convert mbus_format to v4l2_format */
	v4l2_fill_pix_format(&format->fmt.pix, &fmt.format);
	mbus_to_pix(&fmt.format, &format->fmt.pix);

	return 0;
}