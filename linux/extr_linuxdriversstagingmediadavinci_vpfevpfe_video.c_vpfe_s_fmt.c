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
struct v4l2_format {int dummy; } ;
struct vpfe_video_device {struct v4l2_format fmt; scalar_t__ started; struct vpfe_device* vpfe_dev; } ;
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int __vpfe_video_get_format (struct vpfe_video_device*,struct v4l2_format*) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct vpfe_video_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vpfe_s_fmt(struct file *file, void *priv,
				struct v4l2_format *fmt)
{
	struct vpfe_video_device *video = video_drvdata(file);
	struct vpfe_device *vpfe_dev = video->vpfe_dev;
	struct v4l2_format format;
	int ret;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_s_fmt\n");
	/* If streaming is started, return error */
	if (video->started) {
		v4l2_err(&vpfe_dev->v4l2_dev, "Streaming is started\n");
		return -EBUSY;
	}
	/* get adjacent subdev's output pad format */
	ret = __vpfe_video_get_format(video, &format);
	if (ret)
		return ret;
	*fmt = format;
	video->fmt = *fmt;
	return 0;
}