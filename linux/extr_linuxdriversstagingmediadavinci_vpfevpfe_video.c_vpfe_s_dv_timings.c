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
struct vpfe_video_device {TYPE_1__* current_ext_subdev; int /*<<< orphan*/  stdid; struct vpfe_device* vpfe_dev; } ;
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_dv_timings {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  grp_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_STD_UNKNOWN ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  s_dv_timings ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int v4l2_device_call_until_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vpfe_video_device*,int /*<<< orphan*/ ,struct v4l2_dv_timings*) ; 
 struct vpfe_video_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int
vpfe_s_dv_timings(struct file *file, void *fh,
		  struct v4l2_dv_timings *timings)
{
	struct vpfe_video_device *video = video_drvdata(file);
	struct vpfe_device *vpfe_dev = video->vpfe_dev;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_s_dv_timings\n");

	video->stdid = V4L2_STD_UNKNOWN;
	return v4l2_device_call_until_err(&vpfe_dev->v4l2_dev,
					  video->current_ext_subdev->grp_id,
					  video, s_dv_timings, timings);
}