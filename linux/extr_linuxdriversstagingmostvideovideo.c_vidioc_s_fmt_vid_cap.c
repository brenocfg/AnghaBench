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
struct most_video_dev {int dummy; } ;
struct file {int dummy; } ;
struct comp_fh {struct most_video_dev* mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDIOC_S_FMT ; 
 int comp_set_format (struct most_video_dev*,int /*<<< orphan*/ ,struct v4l2_format*) ; 

__attribute__((used)) static int vidioc_s_fmt_vid_cap(struct file *file, void *priv,
				struct v4l2_format *f)
{
	struct comp_fh *fh = priv;
	struct most_video_dev *mdev = fh->mdev;

	return comp_set_format(mdev, VIDIOC_S_FMT, f);
}