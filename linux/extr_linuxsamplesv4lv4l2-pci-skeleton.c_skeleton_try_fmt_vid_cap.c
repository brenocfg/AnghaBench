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
struct v4l2_pix_format {scalar_t__ pixelformat; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct skeleton {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_PIX_FMT_YUYV ; 
 int /*<<< orphan*/  skeleton_fill_pix_format (struct skeleton*,struct v4l2_pix_format*) ; 
 struct skeleton* video_drvdata (struct file*) ; 

__attribute__((used)) static int skeleton_try_fmt_vid_cap(struct file *file, void *priv,
				    struct v4l2_format *f)
{
	struct skeleton *skel = video_drvdata(file);
	struct v4l2_pix_format *pix = &f->fmt.pix;

	/*
	 * Due to historical reasons providing try_fmt with an unsupported
	 * pixelformat will return -EINVAL for video receivers. Webcam drivers,
	 * however, will silently correct the pixelformat. Some video capture
	 * applications rely on this behavior...
	 */
	if (pix->pixelformat != V4L2_PIX_FMT_YUYV)
		return -EINVAL;
	skeleton_fill_pix_format(skel, pix);
	return 0;
}