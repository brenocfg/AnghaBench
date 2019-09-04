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
struct TYPE_3__ {int /*<<< orphan*/  timeperframe; int /*<<< orphan*/  capability; } ;
struct TYPE_4__ {TYPE_1__ output; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_2__ parm; } ;
struct iss_video_fh {int /*<<< orphan*/  timeperframe; } ;
struct iss_video {scalar_t__ type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  V4L2_CAP_TIMEPERFRAME ; 
 int /*<<< orphan*/  memset (struct v4l2_streamparm*,int /*<<< orphan*/ ,int) ; 
 struct iss_video_fh* to_iss_video_fh (void*) ; 
 struct iss_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int
iss_video_get_param(struct file *file, void *fh, struct v4l2_streamparm *a)
{
	struct iss_video_fh *vfh = to_iss_video_fh(fh);
	struct iss_video *video = video_drvdata(file);

	if (video->type != V4L2_BUF_TYPE_VIDEO_OUTPUT ||
	    video->type != a->type)
		return -EINVAL;

	memset(a, 0, sizeof(*a));
	a->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	a->parm.output.capability = V4L2_CAP_TIMEPERFRAME;
	a->parm.output.timeperframe = vfh->timeperframe;

	return 0;
}