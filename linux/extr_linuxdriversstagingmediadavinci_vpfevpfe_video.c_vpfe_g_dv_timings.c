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
struct vpfe_video_device {TYPE_1__* current_ext_subdev; struct vpfe_device* vpfe_dev; } ;
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_dv_timings {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct v4l2_subdev* subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  g_dv_timings ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,struct vpfe_video_device*,int /*<<< orphan*/ ,struct v4l2_dv_timings*) ; 
 struct vpfe_video_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int
vpfe_g_dv_timings(struct file *file, void *fh,
	      struct v4l2_dv_timings *timings)
{
	struct vpfe_video_device *video = video_drvdata(file);
	struct vpfe_device *vpfe_dev = video->vpfe_dev;
	struct v4l2_subdev *subdev = video->current_ext_subdev->subdev;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_g_dv_timings\n");
	return v4l2_subdev_call(subdev, video, g_dv_timings, timings);
}