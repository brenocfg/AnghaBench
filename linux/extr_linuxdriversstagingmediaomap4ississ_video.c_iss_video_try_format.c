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
struct v4l2_subdev_format {int /*<<< orphan*/  format; int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;
struct iss_video {scalar_t__ type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  get_fmt ; 
 int /*<<< orphan*/  iss_video_mbus_to_pix (struct iss_video*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iss_video_pix_to_mbus (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct v4l2_subdev* iss_video_remote_subdev (struct iss_video*,int /*<<< orphan*/ *) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 struct iss_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int
iss_video_try_format(struct file *file, void *fh, struct v4l2_format *format)
{
	struct iss_video *video = video_drvdata(file);
	struct v4l2_subdev_format fmt;
	struct v4l2_subdev *subdev;
	u32 pad;
	int ret;

	if (format->type != video->type)
		return -EINVAL;

	subdev = iss_video_remote_subdev(video, &pad);
	if (!subdev)
		return -EINVAL;

	iss_video_pix_to_mbus(&format->fmt.pix, &fmt.format);

	fmt.pad = pad;
	fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(subdev, pad, get_fmt, NULL, &fmt);
	if (ret)
		return ret;

	iss_video_mbus_to_pix(video, &fmt.format, &format->fmt.pix);
	return 0;
}