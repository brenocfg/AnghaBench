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
struct v4l2_subdev_frame_interval {int /*<<< orphan*/  interval; int /*<<< orphan*/  pad; } ;
struct TYPE_3__ {int /*<<< orphan*/  timeperframe; int /*<<< orphan*/  capability; } ;
struct TYPE_4__ {TYPE_1__ capture; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_2__ parm; } ;
struct file {int dummy; } ;
struct capture_priv {int /*<<< orphan*/  src_sd; int /*<<< orphan*/  src_sd_pad; } ;
typedef  int /*<<< orphan*/  fi ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_CAP_TIMEPERFRAME ; 
 int /*<<< orphan*/  g_frame_interval ; 
 int /*<<< orphan*/  memset (struct v4l2_subdev_frame_interval*,int /*<<< orphan*/ ,int) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_subdev_frame_interval*) ; 
 int /*<<< orphan*/  video ; 
 struct capture_priv* video_drvdata (struct file*) ; 

__attribute__((used)) static int capture_g_parm(struct file *file, void *fh,
			  struct v4l2_streamparm *a)
{
	struct capture_priv *priv = video_drvdata(file);
	struct v4l2_subdev_frame_interval fi;
	int ret;

	if (a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	memset(&fi, 0, sizeof(fi));
	fi.pad = priv->src_sd_pad;
	ret = v4l2_subdev_call(priv->src_sd, video, g_frame_interval, &fi);
	if (ret < 0)
		return ret;

	a->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	a->parm.capture.timeperframe = fi.interval;

	return 0;
}