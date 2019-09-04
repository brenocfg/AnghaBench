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
struct vpfe_video_device {struct vpfe_device* vpfe_dev; } ;
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_format {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int __vpfe_video_get_format (struct vpfe_video_device*,struct v4l2_format*) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct vpfe_video_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vpfe_try_fmt(struct file *file, void *priv,
				  struct v4l2_format *fmt)
{
	struct vpfe_video_device *video = video_drvdata(file);
	struct vpfe_device *vpfe_dev = video->vpfe_dev;
	struct v4l2_format format;
	int ret;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_try_fmt\n");
	/* get adjacent subdev's output pad format */
	ret = __vpfe_video_get_format(video, &format);
	if (ret)
		return ret;

	*fmt = format;
	return 0;
}